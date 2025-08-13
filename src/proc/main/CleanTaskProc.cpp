
#include "CleanTaskProc.h"
#include "../ProcManager.h"
#include "../../io/io.h"
#include "../../util/strutil.h"

#include <iostream>

using std::cout;
using std::endl;

void CleanTaskProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    cout << "\nEXECUTANDO LIMPESA..." << endl;

    MainScript* script = manager->getMainScript();

    string isDll = script->getPropertyValue( "is.dll" );
    string buildDir = script->getPropertyValue( "build.dir" );
    string binDir = script->getPropertyValue( "bin.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );
    string buildFiles = script->getPropertyValue( "build.files" );

    string propName = ( isDll == "true" ? "dll.file.name" : "exe.file.name" );
    string fname = script->getPropertyValue( propName );
    if ( fname != "" ) {
        string file = io::concatPaths( binDir, fname );
        //appRecursiveDeleteFileOrDirectoryIfExists( file, propName, script );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = io::fileOrDirName( bfile );
        fname = io::concatPaths( buildDir, fname );
        appRecursiveDeleteFileOrDirectoryIfExists( fname, "build.files", script );
    }

    manager->executaTaskIfExists( "clean" );

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void CleanTaskProc::appRecursiveDeleteFileOrDirectoryIfExists( string path, string propName, MainScript* script ) {
    Prop* prop = script->getProperty( propName );

    try {
        if ( io::fileExists( path ) ) {
            int count = io::recursiveDeleteFileOrDirectory( path );
            if ( count == 0 )
                throw taskproc_error( prop, "Arquivo ou pasta nao deletado: \"" + path + "\"" );

            cout << "Deletado: " << path << endl;
        }
    } catch ( const io_error& e ) {
        throw taskproc_error( prop, "Nao foi possivel deletar o arquivo ou pasta: \"" + path + "\"" );
    }
}
