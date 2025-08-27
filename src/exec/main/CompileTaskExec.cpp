
#include "CompileTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../compiler/Compiler.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../util/strutil.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

#include <vector>
#include <sstream>
#include <stdexcept>

using std::vector;
using std::stringstream;

void CompileTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );

    bool isVerbose;
    bool isShowCMDOutput;
    if ( isCompileAll || isBuildAll ) {
        isVerbose = manager->getArgManager()->isVerbose( tasks::COMPILEALL );
        isShowCMDOutput = manager->getArgManager()->isShowCMDOutput( tasks::COMPILEALL );
    } else {
        isVerbose = manager->getArgManager()->isVerbose( tasks::COMPILE );
        isShowCMDOutput = manager->getArgManager()->isShowCMDOutput( tasks::COMPILE );
    }

    Output& out = manager->out;
    bool isNoResume = manager->getArgManager()->isNoResume();

    if ( isVerbose )
        out << "\n";
        
    if ( !isNoResume || isVerbose ) {
        if ( isCompileAll || isBuildAll ) {
            out << infos::EXECUTING << " " << output::green( tasks::COMPILEALL ) << "..." << "\n";
        } else {
            out << infos::EXECUTING << " " << output::green( tasks::COMPILE ) << "..." << "\n";
        }
    }

    if ( isCompileAll || isBuildAll )
        manager->executaUserTaskIfExists( tasks::COMPILEALL, TaskExecution::BEFORE );
    else manager->executaUserTaskIfExists( tasks::COMPILE, TaskExecution::BEFORE );

    string compiler = script->getPropertyValue( props::COMPILER );
    string compilerParams = script->getPropertyValue( props::COMPILER_PARAMS );

    string exeFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string includeDirs = script->getPropertyValue( props::INCLUDE_DIRS );
    string libDirs = script->getPropertyValue( props::LIB_DIRS );

    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::absoluteResolvePath( binDir );
    objDir = io::absoluteResolvePath( objDir );

    binDir = io::addSeparatorToDirIfNeed( binDir );
    objDir = io::addSeparatorToDirIfNeed( objDir );

    this->appCreateDirs( binDir, manager );
    this->appCreateDirs( objDir, manager );

    if ( compiler == "" )
        compiler = consts::DEFAULT_COMPILER;

    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos ) {
        string dir = io::dirPath( objDir + info->objFilePath );
        if ( dir != "" )
            this->appCreateDirs( dir, manager );
    }

    vector<CodeInfo*> filesToCompile;
    if ( isCompileAll || isBuildAll ) {
        filesToCompile = sourceCodeInfos;
    } else {
        sourceCodeManager->loadFilesToCompile( filesToCompile, consts::LAST_WRITE_TIMES_FILE );
    }

    Shell* shell = new Shell( out );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );

    for( CodeInfo* sourceCodeInfo : filesToCompile ) {
        Compiler* comp = new Compiler();
        comp->setCompiler( compiler );
        comp->setCompilerParams( compilerParams );
        comp->setDefines( defines );
        comp->setIncludeDirs( includeDirs );
        comp->setObjectCodeFile( objDir + sourceCodeInfo->objFilePath );
        comp->setSourceCodeFile( sourceCodeInfo->filePath );

        string cmdline = comp->buildCMDLine();

        delete comp;

        shell->pushCommand( cmdline );
    }

    int exitCode = shell->executa();
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::COMPILATION_FAILED );

    delete shell;

    sourceCodeManager->saveLastWriteTimesInFile( consts::LAST_WRITE_TIMES_FILE );

    if ( isCompileAll || isBuildAll )
        manager->executaUserTaskIfExists( tasks::COMPILEALL, TaskExecution::AFTER );
    else manager->executaUserTaskIfExists( tasks::COMPILE, TaskExecution::AFTER );

    if ( isVerbose ) {
        if ( filesToCompile.empty() )
            out << infos::COMPILATION_UP_TO_DATE << "\n";
        else out << infos::SUCCESS_IN_COMPILATION << "\n";
    }
}

void CompileTaskExec::appCreateDirs( string dirPath, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* mainCMD = manager->getMainCMD();

    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        messagebuilder b( errors::DIRECTORY_NOT_CREATED );
        b << io::absolutePath( dirPath );
        throw st_error( mainCMD, b.str() );
    }
}
