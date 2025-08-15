
#include "CompileAllTaskProc.h"
#include "../ProcManager.h"
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

void CompileAllTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nCOMPILANDO..." << endl;

    MainScript* script = manager->getMainScript();

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

    io::createDirs( binDir );
    io::createDirs( objDir );

    bool isdll = isDll == "true";

    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();
    vector<string> sourceCodeFilePaths = sourceCodeManager->sourceCodeFilePaths();

    Shell* shell = new Shell( true );
    for( string filePath : sourceCodeFilePaths ) {
        SourceCodeInfo* sourceCodeInfo = sourceCodeManager->getSourceCodeInfo( filePath );

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

        ss << " -o " << io::concatPaths( objDir, sourceCodeInfo->objFilePath );
        ss << " -c " << sourceCodeInfo->filePath;

        shell->pushCommand( ss.str() );
    }
    bool ok = shell->executa();
    if ( !ok )
        throw taskproc_error( "Falha na compilacao!" );

    manager->executaTaskIfExists( tasks::COMPILEALL );

    cout << "Compilacao executada com sucesso!" << endl;
}
