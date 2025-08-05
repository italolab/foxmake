
#include "TaskExec.h"
#include "shell/shell.h"
#include "args/ArgsInter.h"
#include "util/util.h"
#include "util/ioutil.h"

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
            bool isClean = args->existsCommand( "clean" );
            bool isCompile = args->existsCommand( "compile" );
            bool isLink = args->existsCommand( "link" );
            bool isBuild = args->existsCommand( "build" );
            bool isCopy = args->existsCommand( "copy" );

            if ( isBuild ) {
                isClean = true;
                isCompile = true;
                isLink = true;
                isCopy = true;
            }

            if ( isClean )
                clean( args, props );

            if ( isCompile || isLink )
                compileAndLink( args, props, isCompile, isLink );

            if ( isCopy )
                copyFiles( args, props );

        } catch ( const exception& e ) {
            cerr << "Erro: " << e.what() << endl;
        }
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void TaskExec::clean( Args* args, Properties* props ) {
    cout << "EXECUTANDO LIMPESA..." << endl;
}

void TaskExec::copyFiles( Args* args, Properties* props ) {
    cout << "COPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = props->getProperty( "is.dll" );
    string buildDir = props->getProperty( "build.dir" );
    string binDebugDir = props->getProperty( "bin.debug.dir" );

    if ( buildDir != "" )
        createDirectories( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = props->getProperty( "dll.file.name" );
        string fname = makePreferred( concatPaths( binDebugDir, dllFileName ) );
        bool ok = copyFile( fname, buildDir, true );
        if ( !ok )
            throw runtime_error( "Nao foi possivel copiar o arquivo " + dllFileName + " para o diretorio de build." );
    } else {
        string exeFileName = props->getProperty( "exe.file.name" );
        string fname = makePreferred( concatPaths( binDebugDir, exeFileName ) );
        bool ok = copyFile( fname, buildDir, true );
        if ( !ok )
            throw runtime_error( "Nao foi possivel copiar o arquivo " + exeFileName + " para o diretorio de build." );
    }

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void TaskExec::compileAndLink( Args* args, Properties* props, bool isCompile, bool isLink ) {
    cout << "COMPILANDO E/OU LINKANDO..." << endl;

    string isDll = props->getProperty( "is.dll" );

    string srcDir = props->getProperty( "src.dir" );
    string binDebugDir = props->getProperty( "bin.debug.dir" );
    string objDebugDir = props->getProperty( "obj.debug.dir" );

    string includeDirs = props->getProperty( "include.dirs" );
    string libDirs = props->getProperty( "lib.dirs" );
    string dllDirs = props->getProperty( "dll.dirs" );

    string outputDefFile = props->getProperty( "output.def.file" );
    string outImplibFile = props->getProperty( "out.implib.file" );

    string defines = props->getProperty( "defines" );
    string compiler = props->getProperty( "compiler" );
    string exeFileName = props->getProperty( "exe.file.name" );
    string dllFileName = props->getProperty( "dll.file.name" );

    string compilerParams = props->getProperty( "compiler.params" );
    string linkerParams = props->getProperty( "linker.params" );

    createDirectories( binDebugDir );
    createDirectories( objDebugDir );

    bool isdll = isDll == "true";

    vector<CPPFile*> cppFiles;
    bool ok = recursiveProcSrcFiles( srcDir, cppFiles );
    if ( ok ) {
        for( CPPFile* cppFile : cppFiles ) {
            string absFile = concatPaths( objDebugDir, cppFile->objFileName );
            string dir = directoryPath( absFile );
            dir = makePreferred( dir );
            createDirectories( dir );
        }

        if ( isCompile ) {
            Shell* shell = new Shell( true );
            for( CPPFile* cppFile : cppFiles ) {
                stringstream ss;
                ss << compiler << " " << compilerParams;
                if ( isdll ) {
                    stringstream defParams;
                    stringstream incdirParams;
                    string token;

                    istringstream iss( defines );
                    while( getline( iss, token, ' ' ) )
                        defParams << " -D" << token;

                    istringstream iss2( includeDirs );
                    while( getline( iss2, token, ' ' ) )
                        incdirParams << " -I" << token;

                    ss << defParams.str() << incdirParams.str();
                }
                ss << " -o " << makePreferred( concatPaths( objDebugDir, cppFile->objFileName ) );
                ss << " -c " << cppFile->fileName;

                shell->pushCommand( ss.str() );
            }
            ok = shell->executa();
        }

        if ( ok && isLink ) {
            stringstream ss;
            ss << compiler;
            if ( isdll )
                ss << " -shared";
            if ( isdll && outputDefFile != "" )
                ss << " -Wl,--output-def=" << outputDefFile;
            if ( isdll && outImplibFile != "" )
                ss << " -Wl,--out-implib=" << outImplibFile;

            if ( !isdll )
                ss << " -o " << makePreferred( concatPaths( binDebugDir, exeFileName ) );

            if ( isdll ) {
                stringstream libParams;
                stringstream dllParams;
                string token;

                istringstream iss( libDirs );
                while( getline( iss, token, ' ' ) )
                    libParams << " -L" << token;

                istringstream iss2( dllDirs );
                while( getline( iss2, token, ' ' ) )
                    dllParams << " -l" << token;

                ss << libParams.str() << dllParams.str();
            }

            for( CPPFile* cppFile : cppFiles )
                ss << " " << makePreferred(  concatPaths( objDebugDir, cppFile->objFileName ) ) ;

            if ( isdll )
                ss << " -o " << makePreferred( concatPaths( binDebugDir, dllFileName ) );

            Shell* shell = new Shell( true );
            shell->pushCommand( ss.str() );
            ok = shell->executa();
        }

        if ( ok ) {
            cout << "Compilacao e/ou linkagem executada(s) com sucesso!" << endl;
        } else {
            cerr << "Houve falha na execucao de algum comando de compilacao ou linkagem." << endl;
        }
    } else {
        cerr << "Nao foi possivel ler o diretorio: " << srcDir << endl;
    }
}


