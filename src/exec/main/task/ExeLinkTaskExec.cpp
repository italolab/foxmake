
#include "ExeLinkTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../compiler/Linker.h"
#include "../../../darv/MainScript.h"
#include "../../../shell/shell.h"
#include "../../../io/io.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"
#include "../../../consts.h"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::vector;
using std::stringstream;

void ExeLinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );
    string resourceFile = script->getPropertyValue( props::RESOURCE_FILE );
    string testDir = script->getPropertyValue( props::TEST_DIR );

    if ( compiler == "" )
        compiler = consts::DEFAULT_COMPILER;

    if ( outputFileName == "" && testDir == "" ) {
        messagebuilder b( errors::PROPERTY_NOT_DEFINED_FOR_LINKING );
        b << props::OUTPUT_FILE_NAME;
        throw st_error( nullptr, b.str() );
    }

    if ( resourceFile != "" ) {
        if ( !io::fileExists( resourceFile ) ) {
            messagebuilder b( errors::RESOURCE_FILE_NOT_EXISTS );
            b << resourceFile;
            throw st_error( nullptr, b.str() );
        }
    }

    if ( outputFileName != "" )
        this->execLinkage( mgr );

    if ( testDir != "" )
        this->execTestLinkage( mgr );
}

void ExeLinkTaskExec::execLinkage( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::LINK );

    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string resourceFile = script->getPropertyValue( props::RESOURCE_FILE );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string libs = script->getPropertyValue( props::LIBS );
    
    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::absoluteResolvePath( binDir );
    objDir = io::absoluteResolvePath( objDir );

    binDir = io::addSeparatorToDirIfNeed( binDir );
    objDir = io::addSeparatorToDirIfNeed( objDir );

    vector<string> objectCodeFiles;
    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos )        
        objectCodeFiles.push_back( objDir + info->objFilePath );    

    if ( objectCodeFiles.empty() ) {
        out << output::green( infos::NOTHING_TO_LINK ) << "\n";
    } else {
        Linker* linker = new Linker();
        linker->setCompiler( compiler );
        linker->setLinkerParams( linkerParams );
        linker->setDefines( defines );
        linker->setLibraryDirs( libDirs );
        linker->setLibraries( libs );
        linker->setObjectCodeFiles( objectCodeFiles );
        linker->setResourceFile( resourceFile );
        linker->setOutputFile( binDir + outputFileName );
        string cmdline = linker->buildCMDLine();

        delete linker;

        Shell* shell = new Shell( out );
        shell->setVerbose( isVerbose );
        shell->setShowOutput( isShowCMDOutput );
        shell->pushCommand( cmdline );

        int exitCode = shell->execute();
        delete shell;
        if ( exitCode != 0 )
            throw st_error( nullptr, errors::LINKING_FAILED );
    }
}

void ExeLinkTaskExec::execTestLinkage( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    SourceCodeManager* testSourceCodeManager = manager->getTestSourceCodeManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::LINK );

    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    string testLinkerParams = script->getPropertyValue( props::TEST_LINKER_PARAMS );

    string testLibDirs = script->getPropertyValue( props::TEST_LIB_DIRS );
    string testLibs = script->getPropertyValue( props::TEST_LIBS );

    string testDefines = script->getPropertyValue( props::TEST_DEFINES );

    string objDir = script->getPropertyValue( props::OBJ_DIR );
    string binDir = script->getPropertyValue( props::BIN_DIR );

    objDir = io::absoluteResolvePath( objDir );
    binDir = io::absoluteResolvePath( binDir );

    objDir = io::addSeparatorToDirIfNeed( objDir );
    binDir = io::addSeparatorToDirIfNeed( binDir );

    vector<string> withHeaderObjFiles = sourceCodeManager->withHeaderObjectCodeFiles();    
    vector<CodeInfo*> testSourceCodeInfos = testSourceCodeManager->sourceCodeInfos();
        
    vector<string> objectCodeFiles;
    
    for( string objFile : withHeaderObjFiles ) {
        string ofile = objDir + objFile;
        if ( io::fileExists( ofile ) )
            objectCodeFiles.push_back( ofile );
    }

    for( CodeInfo* info : testSourceCodeInfos )
        objectCodeFiles.push_back( objDir + info->objFilePath );

    if ( objectCodeFiles.empty() ) {
        out << output::green( infos::NOTHING_TO_TEST ) << "\n";
    } else {
        Linker* linker = new Linker();
        linker->setCompiler( compiler );
        linker->setLinkerParams( testLinkerParams );
        linker->setDefines( testDefines );
        linker->setLibraryDirs( testLibDirs );
        linker->setLibraries( testLibs );
        linker->setObjectCodeFiles( objectCodeFiles );
        linker->setOutputFile( binDir + consts::TEST_OUTPUT_FILE_NAME );
        string cmdline = linker->buildCMDLine();

        delete linker;

        Shell* shell = new Shell( out );
        shell->setVerbose( isVerbose );
        shell->setShowOutput( isShowCMDOutput );
        shell->pushCommand( cmdline );

        int exitCode = shell->execute();
        delete shell;
        if ( exitCode != 0 )
            throw st_error( nullptr, errors::TEST_LINKING_FAILED );            
    }
}