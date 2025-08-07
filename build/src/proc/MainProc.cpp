
#include "MainProc.h"
#include "../inter/MainInter.h"
#include "../shell/shell.h"
#include "../util/strutil.h"
#include "../io/io.h"
#include "../io/cppio.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

MainProc::MainProc( string cmdName ) : Proc( cmdName ) {}

void MainProc::processa( CMD* cmd, ProcManager* mgr ) {
    MainInter* mainInter = mgr->getMainInter();

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
            clean( cmd, mainInter );

        if ( isCompile || isLink )
            compileAndLink( cmd, mainInter, isCompile, isLink );

        if ( isCopy )
            copyFiles( cmd, mainInter );

        procCMDs( mgr );
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void MainProc::procCMDs( ProcManager* mgr ) {
    MainInter* inter = mgr->getMainInter();
    int tam = inter->getCMDLength();

    if ( tam > 0 )
        cout << "\nEXECUTANDO COMANDOS" << endl;

    for( int i = 0; i < tam; i++ ) {
        CMD* cmd = inter->getCMDByIndex( i );

        Proc* proc = mgr->getProc( cmdName, cmd->getName() );
        if ( proc == nullptr )
            throw runtime_error( "Comando nao encontrado: \"" + cmd->getName() + "\"" );

        proc->processa( cmd, mgr );
        cout << "Executado: " << cmd->getCMDStr() << endl;
    }

    if ( tam > 0 )
        cout << "Comandos executados com sucesso." << endl;
}

void MainProc::clean( CMD* texec, MainInter* inter ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

    string isDll = inter->getPropertyValue( "is.dll" );
    string buildDir = inter->getPropertyValue( "build.dir" );
    string binDebugDir = inter->getPropertyValue( "bin.debug.dir" );
    string objDebugDir = inter->getPropertyValue( "obj.debug.dir" );
    string buildFiles = inter->getPropertyValue( "build.files" );

    string fname;
    if ( isDll == "true" ) {
        fname = inter->getPropertyValue( "dll.file.name" );
    } else {
        fname = inter->getPropertyValue( "exe.file.name" );
    }
    string file = io::concatPaths( binDebugDir, fname );
    appDeleteFileOrDirectory( file );

    cout << "Deletado: " << file << endl;

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = io::fileOrDirName( bfile );
        fname = io::concatPaths( buildDir, fname );
        appDeleteFileOrDirectory( fname );

        cout << "Deletado: " << fname << endl;
    }

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void MainProc::copyFiles( CMD* texec, MainInter* inter ) {
    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = inter->getPropertyValue( "is.dll" );
    string buildDir = inter->getPropertyValue( "build.dir" );
    string binDebugDir = inter->getPropertyValue( "bin.debug.dir" );
    string buildFiles = inter->getPropertyValue( "build.files" );

    if ( buildDir != "" )
        io::createDirectories( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = inter->getPropertyValue( "dll.file.name" );
        string fname = io::concatPaths( binDebugDir, dllFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    } else {
        string exeFileName = inter->getPropertyValue( "exe.file.name" );
        string fname = io::concatPaths( binDebugDir, exeFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        appCopyFileOrDirectoryToBuild( bfile, buildDir );
        cout << "Copiado: " << bfile << endl;
    }

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void MainProc::compileAndLink( CMD* texec, MainInter* inter, bool isCompile, bool isLink ) {
    cout << "\nCOMPILANDO E/OU LINKANDO..." << endl;

    string isDll = inter->getPropertyValue( "is.dll" );

    string srcDir = inter->getPropertyValue( "src.dir" );
    string binDebugDir = inter->getPropertyValue( "bin.debug.dir" );
    string objDebugDir = inter->getPropertyValue( "obj.debug.dir" );

    string includeDirs = inter->getPropertyValue( "include.dirs" );
    string libDirs = inter->getPropertyValue( "lib.dirs" );
    string dllDirs = inter->getPropertyValue( "dll.dirs" );

    string outputDefFile = inter->getPropertyValue( "output.def.file" );
    string outImplibFile = inter->getPropertyValue( "out.implib.file" );

    string defines = inter->getPropertyValue( "defines" );
    string compiler = inter->getPropertyValue( "compiler" );
    string exeFileName = inter->getPropertyValue( "exe.file.name" );
    string dllFileName = inter->getPropertyValue( "dll.file.name" );

    string compilerParams = inter->getPropertyValue( "compiler.params" );
    string linkerParams = inter->getPropertyValue( "linker.params" );

    io::createDirectories( binDebugDir );
    io::createDirectories( objDebugDir );

    bool isdll = isDll == "true";

    vector<CPPFile*> cppFiles;
    bool ok = cppio::recursiveProcSrcFiles( srcDir, cppFiles );
    if ( ok ) {
        for( CPPFile* cppFile : cppFiles ) {
            string absFile = io::concatPaths( objDebugDir, cppFile->objFileName );
            string dir = io::dirPath( absFile );
            io::createDirectories( dir );
        }

        if ( isCompile ) {
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

                ss << " -o " << io::concatPaths( objDebugDir, cppFile->objFileName );
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
                ss << " -o " << io::concatPaths( binDebugDir, exeFileName );

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

            for( CPPFile* cppFile : cppFiles )
                ss << " " << io::concatPaths( objDebugDir, cppFile->objFileName );

            if ( isdll )
                ss << " -o " << io::concatPaths( binDebugDir, dllFileName );

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

void MainProc::appDeleteFileOrDirectory( string path ) {
    try {
        io::deleteFileOrDirectory( path );
    } catch ( const io_error& e ) {
        throw runtime_error( "Não foi possível deletar o arquivo ou pasta: " + path );
    }
}

void MainProc::appCopyFileOrDirectoryToBuild( string path, string buildDir ) {
    if ( !io::fileExists( path ) )
        throw runtime_error( "O arquivo ou pasta: \"" + path + "\" nao existe." );

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirectories( bdir );
        io::copyFileOrDirectory( path, bdir, true );
    } catch ( const io_error& e ) {
        throw runtime_error( "Nao foi possivel copiar o arquivo ou pasta: \"" + path + "\" para a pasta de build." );
    }
}
