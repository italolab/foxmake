
#include "CompileAllTaskProc.h"
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

void CompileAllTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nCOMPILANDO..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( "is.dll" );

    string binDir = script->getPropertyValue( "bin.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );

    string includeDirs = script->getPropertyValue( "include.dirs" );
    string libDirs = script->getPropertyValue( "lib.dirs" );

    string defines = script->getPropertyValue( "defines" );
    string exeFileName = script->getPropertyValue( "exe.file.name" );
    string dllFileName = script->getPropertyValue( "dll.file.name" );

    string compiler = script->getPropertyValue( "compiler" );
    string compilerParams = script->getPropertyValue( "compiler.params" );

    io::createDirs( binDir );
    io::createDirs( objDir );

    bool isdll = isDll == "true";

    vector<CPPFile*>& cppFiles = manager->getCPPFiles();

    Shell* shell = new Shell( true );
    for( CPPFile* cppFile : cppFiles ) {
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

        ss << " -o " << io::concatPaths( objDir, cppFile->objFileName );
        ss << " -c " << cppFile->fileName;

        shell->pushCommand( ss.str() );
    }
    bool ok = shell->executa();
    if ( !ok )
        throw taskproc_error( "Falha na compilacao!" );

    manager->executaTaskIfExists( "compile" );

    cout << "Compilacao executada com sucesso!" << endl;
}
