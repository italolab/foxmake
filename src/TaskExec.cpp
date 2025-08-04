
#include "TaskExec.h"
#include "util.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const string propertiesFileName = "taskexec.properties";

void TaskExec::proc( int argc, char* argv[] ) {
    ArgsInter* inter = new ArgsInter();
    Args* args = inter->exec( argc, argv );

    Properties* props = new Properties();
    props->load( propertiesFileName );

    if ( args->getCommandsLength() > 0 ) {
        string cmd = args->getCommand( 0 );
        if ( cmd == "clean" ) {
            clean( args, props );
        } else if ( cmd == "compile" ) {
            compile( args, props );
        } else if ( cmd == "link" ) {
            link( args, props );
        } else {
            cout << "Comando invalido: " << cmd << endl;
        }
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void TaskExec::clean( Args* args, Properties* props ) {
    int clen = args->getCommandsLength();
    int alen = args->getArgsLength();
    cout << "Comandos: ";
    for( int i = 0; i < clen; i++ )
        cout << args->getCommand( i ) << " ";
    cout << endl;
    cout << "Argumentos: ";
    for( int i = 0; i < alen; i++ )
        cout << args->getArg( i ).name << "=" << args->getArg( i ).value << " ";
    cout << endl;
}

void TaskExec::compile( Args* args, Properties* props ) {
    string includeDirs = props->getProperty( "includeDirs" );
    string defines = props->getProperty( "defines" );
    string compiler = props->getProperty( "compiler" );
    string compilerParams = props->getProperty( "compilerParams" );
    string otherCompileParams = props->getProperty( "otherCompileParams" );
    string srcDir = props->getProperty( "srcDir" );
    string debugDir = props->getProperty( "debugDir" );

    vector<CPPFile> cppFiles;
    bool ok = recursiveProcSrcFiles( srcDir, cppFiles );
    if ( ok ) {
        int tam = cppFiles.size();
        for( int i = 0; i < tam; i++ ) {
            stringstream ss;
            ss << compiler << " " << compilerParams << " " << defines << " " << includeDirs << " " << otherCompileParams;
            ss << " -c " << cppFiles[ i ].fileName;

            cout << ss.str() << endl;
            for( int j = 0; j < (int)cppFiles[ i ].dependencies.size(); j++ )
                cout << "\t" << cppFiles[ i ].dependencies[ j ] << endl;
        }
    } else {
        cout << "Nao foi possivel ler o diretorio: " << srcDir << endl;
    }
}

void TaskExec::link( Args* args, Properties* props ) {

}
