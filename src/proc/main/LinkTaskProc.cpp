
#include "LinkTaskProc.h"
#include "../ProcManager.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

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

    string isDll = script->getPropertyValue( "is.dll" );

    string binDir = script->getPropertyValue( "bin.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );

    string libDirs = script->getPropertyValue( "lib.dirs" );
    string dllDirs = script->getPropertyValue( "dll.dirs" );

    string outputDefFile = script->getPropertyValue( "output.def.file" );
    string outImplibFile = script->getPropertyValue( "out.implib.file" );

    string defines = script->getPropertyValue( "defines" );
    string exeFileName = script->getPropertyValue( "exe.file.name" );
    string dllFileName = script->getPropertyValue( "dll.file.name" );

    string compiler = script->getPropertyValue( "compiler" );
    string linkerParams = script->getPropertyValue( "linker.params" );

    bool isdll = isDll == "true";

    if ( exeFileName == "" ) {
        Prop* prop = script->getProperty( "exe.file.name" );
        throw taskproc_error( prop, "A propriedade \"exe.file.name\" deve ter valor definido para linkagem." );
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

    manager->executaTaskIfExists( "link" );

    cout << "Linkagem executada com sucesso." << endl;
}
