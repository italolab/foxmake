
#include "LinkTaskProc.h"
#include "../ProcManager.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
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

void LinkTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nLINKANDO..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( props::IS_DLL );

    string compiler = script->getPropertyValue( props::COMPILER );
    string linkerParams = script->getPropertyValue( props::LINKER_PARAMS );

    string exeFileName = script->getPropertyValue( props::EXE_FILE_NAME );
    string dllFileName = script->getPropertyValue( props::DLL_FILE_NAME );

    string binDir = script->getPropertyValue( props::BIN_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    string libDirs = script->getPropertyValue( props::LIB_DIRS );
    string dllDirs = script->getPropertyValue( props::DLL_DIRS );

    string outputDefFile = script->getPropertyValue( props::OUTPUT_DEF_FILE );
    string outImplibFile = script->getPropertyValue( props::OUT_IMPLIB_FILE );

    string defines = script->getPropertyValue( props::DEFINES );

    bool isdll = isDll == "true";

    if ( exeFileName == "" ) {
        Prop* prop = script->getProperty( props::EXE_FILE_NAME );
        throw taskproc_error( prop, "A propriedade \"" + props::EXE_FILE_NAME + "\" deve ter valor definido para linkagem." );
    }

    stringstream ss;
    ss << compiler;

    if ( isdll )
        ss << " -shared";
    if ( isdll && outputDefFile != "" )
        ss << " -Wl,--output-def=" << outputDefFile;
    if ( isdll && outImplibFile != "" )
        ss << " -Wl,--out-implib=" << outImplibFile;

    if ( !isdll )
        ss << " -o " << io::concatPaths( binDir, exeFileName );

    if ( isdll ) {
        vector<string> libdirsVect = strutil::splitWithDoubleQuotes( libDirs );
        vector<string> dllsVect = strutil::splitWithDoubleQuotes( dllDirs );

        stringstream libdirParams;
        stringstream dllParams;
        string token;

        for( string libdir : libdirsVect)
            libdirParams << " -L" << libdir;

        for( string dll : dllsVect )
            dllParams << " -l" << dll;

        ss << libdirParams.str() << dllParams.str();
    }

    vector<CPPFile*>& cppFiles = manager->getCPPFiles();
    for( CPPFile* cppFile : cppFiles )
        ss << " " << io::concatPaths( objDir, cppFile->objFileName );

    if ( isdll )
        ss << " -o " << io::concatPaths( binDir, dllFileName );

    ss << " " << linkerParams;

    Shell* shell = new Shell( true );
    shell->pushCommand( ss.str() );

    bool ok = shell->executa();
    if ( !ok )
        throw taskproc_error( "Falha na linkagem!" );

    manager->executaTaskIfExists( tasks::LINK );

    cout << "Linkagem executada com sucesso." << endl;
}
