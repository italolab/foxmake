
#include "CopyTaskProc.h"
#include "../ProcManager.h"
#include "../../darv/MainScript.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void CopyTaskProc::proc( CMD* cmd, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( "is.dll" );
    string buildDir = script->getPropertyValue( "build.dir" );
    string binDir = script->getPropertyValue( "bin.dir" );
    string buildFiles = script->getPropertyValue( "build.files" );

    if ( buildDir != "" )
        io::createDirs( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = script->getPropertyValue( "dll.file.name" );
        string fname = io::concatPaths( binDir, dllFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    } else {
        string exeFileName = script->getPropertyValue( "exe.file.name" );
        string fname = io::concatPaths( binDir, exeFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles )
        appCopyFileOrDirectoryToBuild( bfile, buildDir );

    manager->executaTaskIfExists( "copy" );

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void CopyTaskProc::appCopyFileOrDirectoryToBuild( string path, string buildDir ) {
    if ( !io::fileExists( path ) )
        throw runtime_error( "O arquivo ou pasta: \"" + path + "\" nao existe." );

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirs( bdir );
        io::copyFileOrDirectory( path, bdir, true, true );

        cout << "Copiado: " << path << endl;
    } catch ( const io_error& e ) {
        throw runtime_error( "Nao foi possivel copiar o arquivo ou pasta: \"" + path + "\" para a pasta de build." );
    }
}
