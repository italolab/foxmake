
#include "CompileTaskExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"
#include "../../util/strutil.h"

#include "../../consts.h"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

void CompileTaskExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    MainScript* script = manager->getMainScript();

    cout << "\nCOMPILANDO..." << endl;

    bool isCompileAll = mainCMD->existsArg( tasks::COMPILEALL );
    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );

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

    if ( binDir != "" )
        this->appCreateDirs( mainCMD, binDir );
    if ( objDir != "" )
        this->appCreateDirs( mainCMD, objDir );

    if ( binDir != "" )
        binDir = io::addSeparatorToDirIfNeed( binDir );
    if ( objDir != "" )
        objDir = io::addSeparatorToDirIfNeed( objDir );

    bool isdll = isDll == "true";

    if ( compiler == "" )
        throw st_error( mainCMD, "Nenhum compilador informado. \nDefina a propriedade: \"" + props::COMPILER + "\"" );

    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos ) {
        string dir = io::dirPath( objDir + info->objFilePath );
        if ( dir != "" )
            this->appCreateDirs( mainCMD, dir );
    }

    vector<CodeInfo*> filesToCompile;
    if ( isCompileAll || isBuildAll ) {
        filesToCompile = sourceCodeInfos;
    } else {
        sourceCodeManager->loadFilesToCompile( filesToCompile, consts::WRITING_TIME_ELAPSED_FILE );
    }

    Shell* shell = new Shell( true );

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

    int exitCode = shell->executa();
    if ( exitCode != 0 )
        throw st_error( "Falha na compilacao!" );

    delete shell;

    sourceCodeManager->saveWritingTimeElapsedInFile( consts::WRITING_TIME_ELAPSED_FILE );

    if ( isCompileAll || isBuildAll )
        manager->executaTaskIfExists( tasks::COMPILEALL );
    else manager->executaTaskIfExists( tasks::COMPILE );

    if ( filesToCompile.empty() )
        cout << "Nao foi necessario compilar algum arquivo.\nCompilacao atualizada!" << endl;
    else cout << "Compilacao executada com sucesso!" << endl;
}

void CompileTaskExec::appCreateDirs( CMD* mainCMD, string dirPath ) {
    try {
        io::createDirs( dirPath );
    } catch ( const io_error& e ) {
        string absDirPath = io::absolutePath( dirPath );
        throw st_error( mainCMD, "Nao foi possivel criar o diretorio: \"" + absDirPath + "\"" );
    }
}
