
#include "MainProc.h"
#include "../inter/block/MainInter.h"
#include "../shell/shell.h"
#include "../util/strutil.h"
#include "../io/io.h"
#include "../io/cppio.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

MainProc::MainProc( string cmdName ) : Proc( cmdName ) {}

void MainProc::processa( CMDInter* inter, ProcManager* mgr ) {
    MainInter* mainInter = mgr->getMainInter();

    if ( inter->getArgsLength() > 0 ) {
        bool isClean = inter->existsArg( "clean" );
        bool isCompile = inter->existsArg( "compile" );
        bool isLink = inter->existsArg( "link" );
        bool isBuild = inter->existsArg( "build" );
        bool isCopy = inter->existsArg( "copy" );

        if ( isBuild ) {
            isClean = true;
            isCompile = true;
            isLink = true;
            isCopy = true;
        }

        if ( isClean )
            clean( inter, mainInter );

        if ( isCompile || isLink )
            compileAndLink( inter, mainInter, isCompile, isLink );

        if ( isCopy )
            copyFiles( inter, mainInter );

        procCMDs( mgr );
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void MainProc::procCMDs( ProcManager* mgr ) {
    MainInter* mainInter = mgr->getMainInter();
    int tam = mainInter->getCMDsLength();

    if ( tam > 0 )
        cout << "\nEXECUTANDO COMANDOS" << endl;

    for( int i = 0; i < tam; i++ ) {
        CMDInter* cmd = mainInter->getCMDByIndex( i );

        Proc* proc = mgr->getProc( cmdName, cmd->getName() );
        if ( proc == nullptr )
            throw runtime_error( "Comando nao encontrado: \"" + cmd->getName() + "\"" );

        proc->processa( cmd, mgr );
        cout << "Executado: " << cmd->getCMDStr() << endl;
    }

    if ( tam > 0 )
        cout << "Comandos executados com sucesso." << endl;
}

void MainProc::clean( CMDInter* inter, MainInter* mainInter ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

    string isDll = mainInter->getPropertyValue( "is.dll" );
    string buildDir = mainInter->getPropertyValue( "build.dir" );
    string binDir = mainInter->getPropertyValue( "bin.dir" );
    string objDir = mainInter->getPropertyValue( "obj.dir" );
    string buildFiles = mainInter->getPropertyValue( "build.files" );

    string fname;
    if ( isDll == "true" ) {
        fname = mainInter->getPropertyValue( "dll.file.name" );
    } else {
        fname = mainInter->getPropertyValue( "exe.file.name" );
    }

    if ( fname != "" ) {
        string file = io::concatPaths( binDir, fname );
        appDeleteFileOrDirectory( file );

        cout << "Deletado: " << file << endl;
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        string fname = io::fileOrDirName( bfile );
        fname = io::concatPaths( buildDir, fname );
        appDeleteFileOrDirectory( fname );

        cout << "Deletado: " << fname << endl;
    }

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void MainProc::copyFiles( CMDInter* inter, MainInter* mainInter ) {
    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = mainInter->getPropertyValue( "is.dll" );
    string buildDir = mainInter->getPropertyValue( "build.dir" );
    string binDir = mainInter->getPropertyValue( "bin.dir" );
    string buildFiles = mainInter->getPropertyValue( "build.files" );

    if ( buildDir != "" )
        io::createDirectories( buildDir );

    if ( isDll == "true" ) {
        string dllFileName = mainInter->getPropertyValue( "dll.file.name" );
        string fname = io::concatPaths( binDir, dllFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    } else {
        string exeFileName = mainInter->getPropertyValue( "exe.file.name" );
        string fname = io::concatPaths( binDir, exeFileName );
        appCopyFileOrDirectoryToBuild( fname, buildDir );
    }

    vector<string> bfiles = strutil::splitWithDoubleQuotes( buildFiles );
    for( string bfile : bfiles ) {
        appCopyFileOrDirectoryToBuild( bfile, buildDir );
        cout << "Copiado: " << bfile << endl;
    }

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void MainProc::compileAndLink( CMDInter* inter, MainInter* mainInter, bool isCompile, bool isLink ) {
    cout << "\nCOMPILANDO E/OU LINKANDO..." << endl;

    string isDll = mainInter->getPropertyValue( "is.dll" );

    string srcDir = mainInter->getPropertyValue( "src.dir" );
    string binDir = mainInter->getPropertyValue( "bin.dir" );
    string objDir = mainInter->getPropertyValue( "obj.dir" );

    string includeDirs = mainInter->getPropertyValue( "include.dirs" );
    string libDirs = mainInter->getPropertyValue( "lib.dirs" );
    string dllDirs = mainInter->getPropertyValue( "dll.dirs" );

    string outputDefFile = mainInter->getPropertyValue( "output.def.file" );
    string outImplibFile = mainInter->getPropertyValue( "out.implib.file" );

    string defines = mainInter->getPropertyValue( "defines" );
    string compiler = mainInter->getPropertyValue( "compiler" );
    string exeFileName = mainInter->getPropertyValue( "exe.file.name" );
    string dllFileName = mainInter->getPropertyValue( "dll.file.name" );

    string compilerParams = mainInter->getPropertyValue( "compiler.params" );
    string linkerParams = mainInter->getPropertyValue( "linker.params" );

    io::createDirectories( binDir );
    io::createDirectories( objDir );

    bool isdll = isDll == "true";

    vector<CPPFile*> cppFiles;
    bool ok = cppio::recursiveProcSrcFiles( srcDir, cppFiles );
    if ( ok ) {
        for( CPPFile* cppFile : cppFiles ) {
            string absFile = io::concatPaths( objDir, cppFile->objFileName );
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

                ss << " -o " << io::concatPaths( objDir, cppFile->objFileName );
                ss << " -c " << cppFile->fileName;

                shell->pushCommand( ss.str() );
            }
            ok = shell->executa();
        }

        if ( ok && isLink ) {
            if ( exeFileName == "" )
                throw runtime_error( "A propriedade \"exe.file.name\" deve ter valor definido para linkagem." );

            stringstream ss;
            ss << compiler;
            if ( isdll )
                ss << " -shared";
            if ( isdll && outputDefFile != "" )
                ss << " -Wl,--output-def=" << outputDefFile;
            if ( isdll && outImplibFile != "" )
                ss << " -Wl,--out-implib=" << outImplibFile;

            if ( !isdll )
                ss << " -o " << io::concatPaths( binDir, exeFileName );

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
                ss << " " << io::concatPaths( objDir, cppFile->objFileName );

            if ( isdll )
                ss << " -o " << io::concatPaths( binDir, dllFileName );

            ss << " " << linkerParams;

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
        throw runtime_error( "Nao foi possivel deletar o arquivo ou pasta: " + path );
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
