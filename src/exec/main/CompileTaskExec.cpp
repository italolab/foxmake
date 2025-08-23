
#include "CompileTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

void CompileTaskExec::exec( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    MainScript* script = manager->getMainScript();
    CMD* mainCMD = manager->getMainCMD();

    bool isVerbose = manager->isVerbose();
    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );

    if ( isVerbose )
        cout << endl;
        
    if ( isCompileAll || isBuildAll )
        cout << infos::EXECUTING << " " << tasks::COMPILEALL << "..." << endl;
    else cout << infos::EXECUTING << " " << tasks::COMPILE << "..." << endl;

    string isDll = script->getPropertyValue( props::IS_DLL );

    string compiler = script->getPropertyValue( props::COMPILER );
    string compilerParams = script->getPropertyValue( props::COMPILER_PARAMS );

    string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
    string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string includeDirs = script->getPropertyValue( props::INCLUDE_DIRS );
    string libDirs = script->getPropertyValue( props::LIB_DIRS );

    string defines = script->getPropertyValue( props::DEFINES );

    binDir = io::absoluteResolvedPath( binDir );
    objDir = io::absoluteResolvedPath( objDir );

    if ( binDir != "" )
        this->appCreateDirs( binDir, manager );
    if ( objDir != "" )
        this->appCreateDirs( objDir, manager );

    if ( binDir != "" )
        binDir = io::addSeparatorToDirIfNeed( binDir );
    if ( objDir != "" )
        objDir = io::addSeparatorToDirIfNeed( objDir );

    bool isdll = isDll == "true";

    if ( compiler == "" ) {
        messagebuilder b( errors::COMPILER_NOT_INFORMED );
        b << props::COMPILER;
        throw st_error( mainCMD, b.str() );
    }

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
        sourceCodeManager->loadFilesToCompile( filesToCompile, consts::WRITING_TIME_ELAPSED_FILE );
    }

    Shell* shell = new Shell();

    for( CodeInfo* sourceCodeInfo : filesToCompile ) {
        stringstream ss;
        ss << compiler << " " << compilerParams;

        if ( defines != "" ) {
            vector<string> definesVect = strutil::splitWithDoubleQuotes( defines );

            stringstream defParams;
            for( string define : definesVect )
                defParams << " -D" << define;
            ss << defParams.str();
        }

        if ( includeDirs != "" ) {
            vector<string> includeDirsVect = strutil::splitWithDoubleQuotes( includeDirs );

            stringstream incDirsParams;
            for( string incDir : includeDirsVect )
                incDirsParams << " -I" << incDir;
            ss << incDirsParams.str();
        }

        if ( isdll ) {
            vector<string> incdirsVect = strutil::splitWithDoubleQuotes( includeDirs );

            stringstream incdirParams;
            for( string incdir : incdirsVect )
                incdirParams << " -I" << incdir;
            ss << incdirParams.str();
        }

        ss << " -o " << objDir << sourceCodeInfo->objFilePath;
        ss << " -c " << sourceCodeInfo->filePath;

        shell->pushCommand( ss.str() );
    }

    int exitCode = shell->executa( isVerbose );
    if ( exitCode != 0 )
        throw st_error( nullptr, errors::COMPILATION_FAILED );

    delete shell;

    sourceCodeManager->saveWritingTimeElapsedInFile( consts::WRITING_TIME_ELAPSED_FILE );

    if ( isCompileAll || isBuildAll )
        manager->executaUserTask( tasks::COMPILEALL );
    else manager->executaUserTask( tasks::COMPILE );

    if ( isVerbose ) {
        if ( filesToCompile.empty() )
            cout << infos::COMPILATION_UP_TO_DATE << endl;
        else cout << infos::SUCCESS_IN_COMPILATION << endl;
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
