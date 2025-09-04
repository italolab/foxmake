
#include "DynamicLibraryLinkTaskExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../compiler/DynamicLibraryLinker.h"
#include "../../../darv/MainScript.h"
#include "../../../shell/shell.h"
#include "../../../io/io.h"
#include "../../../sourcecode/SourceCodeManager.h"
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
using std::endl;

void DynamicLibraryLinkTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( tasks::LINK );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( tasks::LINK );
    
    MainScript* script = manager->getMainScript();

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string outputFileName = script->getPropertyValue( props::OUTPUT_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string libs = script->getPropertyValue( props::LIBS );

    string outputDefFile = script->getPropertyValue( props::OUTPUT_DEF_FILE );
    string outImplibFile = script->getPropertyValue( props::OUT_IMPLIB_FILE );

    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::path::absoluteResolvePath( binDir );
    objDir = io::path::absoluteResolvePath( objDir );

    binDir = io::path::addSeparatorIfNeed( binDir );
    objDir = io::path::addSeparatorIfNeed( objDir );

    if ( compiler == "" )
        compiler = consts::DEFAULT_COMPILER;    

    string outputFile;
    if ( outputFileName == "" ) {
        messagebuilder b( errors::PROPERTY_NOT_DEFINED_FOR_LINKING );
        b << props::OUTPUT_FILE_NAME;
        throw st_error( nullptr, b.str() );
    }

    vector<string> objectCodeFiles;
    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos )
        objectCodeFiles.push_back( objDir + info->objFilePath );

    if ( objectCodeFiles.empty() ) {
        out << output::green( infos::NOTHING_TO_LINK ) << endl;
    } else {
        DynamicLibraryLinker* linker = new DynamicLibraryLinker();
        linker->setCompiler( compiler );
        linker->setLinkerParams( linkerParams );
        linker->setDefines( defines );
        linker->setLibraryDirs( libDirs );
        linker->setLibraries( libs );
        linker->setObjectCodeFiles( objectCodeFiles );
        linker->setOutputDefFile( outputDefFile );
        linker->setOutImplibFile( outImplibFile );
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
