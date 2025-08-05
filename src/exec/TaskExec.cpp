
#include "TaskExec.h"
#include "CPProc.h"
#include "../shell/shell.h"
#include "../util/util.h"
#include "../util/ioutil.h"
#include "../util/utilexcept.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

const string configFileName = "config.txt";

TaskExec::TaskExec() {
    validCMDs[ "cp" ] = new CPProc();
}

void TaskExec::proc( int argc, char* argv[] ) {
    CMD* cmd = new CMD();
    try {
        cmd->interpreta( argc, argv );

        vector<string> cmdKeys = validCMDsKeys();

        Config* config = new Config();
        config->load( configFileName, cmdKeys );

        if ( cmd->getArgsLength() > 0 ) {
            bool isClean = cmd->existsArg( "clean" );
            bool isCompile = cmd->existsArg( "compile" );
            bool isLink = cmd->existsArg( "link" );
            bool isBuild = cmd->existsArg( "build" );
            bool isCopy = cmd->existsArg( "copy" );

            if ( isBuild ) {
                isClean = true;
                isCompile = true;
                isLink = true;
                isCopy = true;
            }

            if ( isClean )
                clean( cmd, config );

            if ( isCompile || isLink )
                compileAndLink( cmd, config, isCompile, isLink );

            if ( isCopy )
                copyFiles( cmd, config );

            procCMDs( config );
        } else {
            cout << "Nenhum comando informado." << endl;
        }
    } catch ( const exception& e ) {
        cerr << "Erro: " << e.what() << endl;
    }
}

void TaskExec::procCMDs( Config* config ) {
    int tam = config->getCMDLength();

    if ( tam > 0 )
        cout << "EXECUTANDO COMANDOS" << endl;

    for( int i = 0; i < tam; i++ ) {
        CMD* cmd = config->getCMDByIndex( i );
        if ( validCMDs.find( cmd->getName() ) == validCMDs.end() )
            throw runtime_error( "Comando nao encontrado: \"" + cmd->getName() + "\"" );

        Proc proc = validCMDs[ cmd->getName() ];
        proc->proc( cmd, config );
        cout << "Executado: " << cmd->getCMDStr() << endl;
    }

    if ( tam > 0 )
        cout << "Comandos executados com sucesso." << endl;
}

void TaskExec::clean( CMD* texec, Config* config ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

    string isDll = config->getPropertyValue( "is.dll" );
    string buildDir = config->getPropertyValue( "build.dir" );
    string binDebugDir = config->getPropertyValue( "bin.debug.dir" );
    string objDebugDir = config->getPropertyValue( "obj.debug.dir" );
    string buildFiles = config->getPropertyValue( "build.files" );

    string fname;
    if ( isDll == "true" ) {
        fname = config->getPropertyValue( "dll.file.name" );
    } else {
        fname = config->getPropertyValue( "exe.file.name" );
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

void TaskExec::copyFiles( CMD* texec, Config* config ) {
    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = config->getPropertyValue( "is.dll" );
    string buildDir = config->getPropertyValue( "build.dir" );
    string binDebugDir = config->getPropertyValue( "bin.debug.dir" );
    string buildFiles = config->getPropertyValue( "build.files" );

    if ( buildDir != "" )
        createDirectories( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = config->getPropertyValue( "dll.file.name" );
        string fname = concatPaths( binDebugDir, dllFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    } else {
        string exeFileName = config->getPropertyValue( "exe.file.name" );
        string fname = concatPaths( binDebugDir, exeFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    }

    vector<string> bfiles = splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        appCopyFileOrDirectoryToBuild( bfile, buildDir );
        cout << "Copiado: " << bfile << endl;
    }

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void TaskExec::compileAndLink( CMD* texec, Config* config, bool isCompile, bool isLink ) {
    cout << "\nCOMPILANDO E/OU LINKANDO..." << endl;

    string isDll = config->getPropertyValue( "is.dll" );

    string srcDir = config->getPropertyValue( "src.dir" );
    string binDebugDir = config->getPropertyValue( "bin.debug.dir" );
    string objDebugDir = config->getPropertyValue( "obj.debug.dir" );

    string includeDirs = config->getPropertyValue( "include.dirs" );
    string libDirs = config->getPropertyValue( "lib.dirs" );
    string dllDirs = config->getPropertyValue( "dll.dirs" );

    string outputDefFile = config->getPropertyValue( "output.def.file" );
    string outImplibFile = config->getPropertyValue( "out.implib.file" );

    string defines = config->getPropertyValue( "defines" );
    string compiler = config->getPropertyValue( "compiler" );
    string exeFileName = config->getPropertyValue( "exe.file.name" );
    string dllFileName = config->getPropertyValue( "dll.file.name" );

    string compilerParams = config->getPropertyValue( "compiler.params" );
    string linkerParams = config->getPropertyValue( "linker.params" );

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
        throw runtime_error( "Nao foi possivel ler o diretorio: \"" + srcDir + "\"" );
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
    if ( !fileExists( path ) )
        throw runtime_error( "O arquivo ou pasta: \"" + path + "\" nao existe." );

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        createDirectories( bdir );
        copyFileOrDirectory( path, bdir, true );
    } catch ( const io_error& e ) {
        throw runtime_error( "Nao foi possivel copiar o arquivo ou pasta: \"" + path + "\" para a pasta de build." );
    }
}

vector<string> TaskExec::validCMDsKeys() {
    vector<string> keys;
    for( const auto& pair : validCMDs )
        keys.push_back( pair.first );
    return keys;
}
