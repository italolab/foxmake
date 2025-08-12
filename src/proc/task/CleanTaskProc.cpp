
#include "CleanTaskProc.h"
#include "../../darv/MainScript.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

void CleanTaskProc::processa( CMD* cmd, ProcManager* manager ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( "is.dll" );
    string buildDir = script->getPropertyValue( "build.dir" );
    string binDir = script->getPropertyValue( "bin.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );
    string buildFiles = script->getPropertyValue( "build.files" );

    string fname;
    if ( isDll == "true" ) {
        fname = script->getPropertyValue( "dll.file.name" );
    } else {
        fname = script->getPropertyValue( "exe.file.name" );
    }

    if ( fname != "" ) {
        string file = io::concatPaths( binDir, fname );
        //appRecursiveDeleteFileOrDirectoryIfExists( file );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = io::fileOrDirName( bfile );
        fname = io::concatPaths( buildDir, fname );
        appRecursiveDeleteFileOrDirectoryIfExists( fname );
    }

    manager->executaTaskIfExists( "clean" );

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void CleanTaskProc::appRecursiveDeleteFileOrDirectoryIfExists( string path ) {
    try {
        if ( io::fileExists( path ) ) {
            int count = io::recursiveDeleteFileOrDirectory( path );
            if ( count == 0 )
                throw runtime_error( "Arquivo ou pasta nao deletado: \"" + path + "\"" );

            cout << "Deletado: " << path << endl;
        }
    } catch ( const io_error& e ) {
        throw runtime_error( "Nao foi possivel deletar o arquivo ou pasta: \"" + path + "\"" );
    }
}
