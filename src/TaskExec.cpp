
#include "TaskExec.h"
#include "appexcept.h"
#include "shell.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

const string propertiesFileName = "taskexec.properties";

void TaskExec::proc( int argc, char* argv[] ) {
    ArgsInter* inter = new ArgsInter();
    Args* args = inter->exec( argc, argv );

    Properties* props = new Properties();
    props->load( propertiesFileName );

    if ( args->getCommandsLength() > 0 ) {
        string cmd = args->getCommand( 0 );

        try {
            if ( args->existsCommand( "clean" ) )
                clean( args, props );

            bool isCompile = args->existsCommand( "compile" );
            bool isLink = args->existsCommand( "link" );
            if ( isCompile || isLink )
                compileAndLink( args, props, isCompile, isLink );

        } catch ( const exception& e ) {
            cerr << "Erro: " << e.what() << endl;
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

void TaskExec::compileAndLink( Args* args, Properties* props, bool isCompile, bool isLink ) {
    string includeDirs = props->getProperty( "includeDirs" );
    string defines = props->getProperty( "defines" );
    string compiler = props->getProperty( "compiler" );
    string compilerParams = props->getProperty( "compilerParams" );
    string otherCompileParams = props->getProperty( "otherCompileParams" );
    string srcDir = props->getProperty( "srcDir" );
    string binDebugDir = props->getProperty( "binDebugDir" );
    string objDebugDir = props->getProperty( "objDebugDir" );
    string exeFileName = props->getProperty( "exeFileName" );

    vector<CPPFile*> cppFiles;
    bool ok = recursiveProcSrcFiles( srcDir, cppFiles );
    if ( ok ) {
        //vector<string> orderCPPFiles;
        //ordersCPPFilesByDependencies( cppFiles, orderCPPFiles );

        Shell* shell = new Shell( true );
        if ( isCompile ) {
            for( CPPFile* cppFile : cppFiles ) {
                string ofile = cppFile->fileName;
                ofile.replace( ofile.length()-3, 3, "o" );

                stringstream ss;
                ss << compiler << " " << compilerParams << " " << defines << " " << includeDirs << " " << otherCompileParams;
                ss << " -o " << ofile  << " -c " << cppFile->fileName;

                shell->pushCommand( ss.str() );
            }
        }

        if ( isLink ) {
            stringstream ss;
            ss << compiler << " -o " << exeFileName;

            for( CPPFile* cppFile : cppFiles ) {
                string ofile = cppFile->fileName;
                ofile.replace( ofile.length()-3, 3, "o" );
            }
        }

        bool result = shell->executa();
        if ( result ) {
            cout << "Compilado com sucesso!" << endl;
        } else {
            cerr << "Erro na compilacao de um ou mais arquivos." << endl;
        }
    } else {
        cerr << "Nao foi possivel ler o diretorio: " << srcDir << endl;
    }
}

void TaskExec::ordersCPPFilesByDependencies( vector<CPPFile*>& cppFiles, vector<string>& cppFilesInOrder ) {
    for( CPPFile* file : cppFiles )
        ordersCPPFilesDependencies( cppFiles, cppFilesInOrder, file->fileName );
}

void TaskExec::ordersCPPFilesDependencies( vector<CPPFile*>& cppFiles, vector<string>& cppFilesInOrder, string cppFile ) {
    if ( existsInVector( cppFilesInOrder, cppFile ) )
        return;

    CPPFile* file = getCPPFileByFileName( cppFiles, cppFile );
    if ( file == nullptr )
        throw app_error( "Arquivo CPP não encontrado na lista: " + cppFile );

    vector<string>& deps = file->dependencies;
    for( string dep : deps )
        if ( !existsInVector( cppFilesInOrder, dep ) )
            ordersCPPFilesDependencies( cppFiles, cppFilesInOrder, dep );

    cppFilesInOrder.push_back( cppFile );
}


