
#include "LinkTaskProc.h"
#include "../../darv/MainScript.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::vector;
using std::stringstream;

void LinkTaskProc::processa( CMD* cmd, ProcManager* manager ) {
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

    if ( exeFileName == "" )
        throw proc_error( cmd, "A propriedade \"exe.file.name\" deve ter valor definido para linkagem." );

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
        throw runtime_error( "Falha na linkagem!" );

    manager->executaTaskIfExists( "link" );

    cout << "Linkagem executada com sucesso." << endl;
}
