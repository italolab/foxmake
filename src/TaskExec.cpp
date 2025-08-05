
#include "TaskExec.h"
#include "shell/shell.h"
#include "args/ArgsInter.h"
#include "util/util.h"
#include "util/ioutil.h"
#include "util/utilexcept.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

const string propertiesFileName = "taskexec.properties";

void TaskExec::proc( int argc, char* argv[] ) {
    ArgsInter* inter = new ArgsInter();
    try {
        Args* args = inter->exec( argc, argv );

        Properties* props = new Properties();
        props->load( propertiesFileName );

        if ( args->getCommandsLength() > 0 ) {
            string cmd = args->getCommand( 0 );

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
        } else {
            cout << "Nenhum comando informado." << endl;
        }
    } catch ( const exception& e ) {
        cerr << "Erro: " << e.what() << endl;
    }
}

void TaskExec::clean( Args* args, Properties* props ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

    string isDll = props->getProperty( "is.dll" );
    string buildDir = props->getProperty( "build.dir" );
    string binDebugDir = props->getProperty( "bin.debug.dir" );
    string objDebugDir = props->getProperty( "obj.debug.dir" );
    string buildFiles = props->getProperty( "build.files" );

    string fname;
    if ( isDll == "true" ) {
        fname = props->getProperty( "dll.file.name" );
    } else {
        fname = props->getProperty( "exe.file.name" );
    }
    string file = concatPaths( binDebugDir, fname );
    appDeleteFileOrDirectory( file );

    cout << "Deletado: " << file << endl;

    vector<string> bfiles = splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = fileOrDirName( bfile );
        fname = concatPaths( buildDir, fname );
        appDeleteFileOrDirectory( fname );

        cout << "Deletado: " << fname << endl;
    }

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void TaskExec::copyFiles( Args* args, Properties* props ) {
    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = props->getProperty( "is.dll" );
    string buildDir = props->getProperty( "build.dir" );
    string binDebugDir = props->getProperty( "bin.debug.dir" );
    string buildFiles = props->getProperty( "build.files" );

    if ( buildDir != "" )
        createDirectories( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = props->getProperty( "dll.file.name" );
        string fname = concatPaths( binDebugDir, dllFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    } else {
        string exeFileName = props->getProperty( "exe.file.name" );
        string fname = concatPaths( binDebugDir, exeFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    }

    vector<string> bfiles = splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        appCopyFileOrDirectoryToBuild( bfile, buildDir );
        appCopyFileOrDirectoryToBuild( bfile, buildDir );
        cout << "Copiado: " << bfile << endl;
    }

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void TaskExec::compileAndLink( Args* args, Properties* props, bool isCompile, bool isLink ) {
    cout << "\nCOMPILANDO E/OU LINKANDO..." << endl;

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
            createDirectories( dir );
        }

        if ( isCompile ) {
            Shell* shell = new Shell( true );
            for( CPPFile* cppFile : cppFiles ) {
                stringstream ss;
                ss << compiler << " " << compilerParams;

                if ( defines != "" ) {
                    vector<string> definesVect = splitWithDoubleQuotes( defines );

                    stringstream defParams;
                    for( string define : definesVect )
                        defParams << " -D" << define;
                    ss << defParams.str();
                }

                if ( isdll ) {
                    vector<string> incdirsVect = splitWithDoubleQuotes( includeDirs );

                    stringstream incdirParams;
                    for( string incdir : incdirsVect )
                        incdirParams << " -I" << incdir;
                    ss << incdirParams.str();
                }

                ss << " -o " << concatPaths( objDebugDir, cppFile->objFileName );
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
                ss << " -o " << concatPaths( binDebugDir, exeFileName );

            if ( isdll ) {
                vector<string> libdirsVect = splitWithDoubleQuotes( libDirs );
                vector<string> dllsVect = splitWithDoubleQuotes( dllDirs );

                stringstream libdirParams;
                stringstream dllParams;
                string token;

                for( string libdir : libdirsVect)
                    libdirParams << " -L" << libdir;

                for( string dll : dllsVect )
                    dllParams << " -l" << dll;

                ss << libdirParams.str() << dllParams.str();
            }

            for( CPPFile* cppFile : cppFiles )
                ss << " " << concatPaths( objDebugDir, cppFile->objFileName );

            if ( isdll )
                ss << " -o " << concatPaths( binDebugDir, dllFileName );

            Shell* shell = new Shell( true );
            shell->pushCommand( ss.str() );
            ok = shell->executa();
        }

        if ( ok ) {
            cout << "Compilacao e/ou linkagem executada(s) com sucesso!" << endl;
        } else {
            throw runtime_error( "Houve falha na execucao de algum comando de compilacao ou linkagem." );
        }
    } else {
        throw runtime_error( "Nao foi possivel ler o diretorio: " + srcDir );
    }
}

void TaskExec::appDeleteFileOrDirectory( string path ) {
    try {
        deleteFileOrDirectory( path );
    } catch ( const io_error& e ) {
        throw runtime_error( "Não foi possível deletar o arquivo ou pasta: " + path );
    }
}

void TaskExec::appCopyFileOrDirectoryToBuild( string path, string buildDir ) {
    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        createDirectories( bdir );
        copyFileOrDirectory( path, bdir, true );
    } catch ( const io_error& e ) {
        cerr << e.what() << endl;
        throw runtime_error( "Nao foi possivel copiar o arquivo ou pasta: " + path + " para a pasta de build." );
    }
}

