
#include "MainProc.h"
#include "../darv/CMD.h"
#include "../shell/shell.h"
#include "../util/strutil.h"
#include "../io/io.h"
#include "../io/cppio.h"

#include <iostream>
#include <sstream>
#include <vector>

void MainProc::processa( CMD* cmd, ProcManager* manager ) {
    MainScript* script = manager->getMainScript();

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
            clean( cmd, script, manager );

        if ( isCompile || isLink )
            compileAndLink( cmd, script, manager, isCompile, isLink );

        if ( isCopy )
            copyFiles( cmd, script, manager );

        if ( isBuild )
            executaTaskIfExists( "build", manager );

        vector<string> names = script->taskNames();
        for( string taskName : names )
            if ( !isDefaultTask( taskName ) )
                executaTaskIfExists( taskName, manager );

        procCMDs( manager );
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void MainProc::procCMDs( ProcManager* mgr ) {
    MainScript* script = mgr->getMainScript();
    int tam = script->getCMDsLength();

    if ( tam > 0 )
        cout << "\nEXECUTANDO COMANDOS" << endl;

    for( int i = 0; i < tam; i++ ) {
        CMD* cmd = script->getCMDByIndex( i );

        Proc* proc = mgr->getProc( cmd->getName() );
        if ( proc == nullptr )
            throw runtime_error( "Comando nao encontrado: \"" + cmd->getName() + "\"" );

        proc->processa( cmd, mgr );
    }

    if ( tam > 0 )
        cout << "Comandos executados com sucesso." << endl;
}

void MainProc::clean( CMD* cmd, MainScript* script, ProcManager* manager ) {
    cout << "\nEXECUTANDO LIMPESA..." << endl;

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

    executaTaskIfExists( "clean", manager );

    cout << "Limpesa efetuada com sucesso!" << endl;
}

void MainProc::copyFiles( CMD* cmd, MainScript* script, ProcManager* manager ) {
    cout << "\nCOPIANDO ARQUIVOS DE BUILD..." << endl;

    string isDll = script->getPropertyValue( "is.dll" );
    string buildDir = script->getPropertyValue( "build.dir" );
    string binDir = script->getPropertyValue( "bin.dir" );
    string buildFiles = script->getPropertyValue( "build.files" );

    if ( buildDir != "" )
        io::createDirectories( buildDir );

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

    executaTaskIfExists( "copy", manager );

    cout << "Arquivos de build copiados com sucesso!" << endl;
}

void MainProc::compileAndLink( CMD* cmd, MainScript* script, ProcManager* manager, bool isCompile, bool isLink ) {
    cout << "\nCOMPILANDO E/OU LINKANDO..." << endl;

    string isDll = script->getPropertyValue( "is.dll" );

    string srcDir = script->getPropertyValue( "src.dir" );
    string binDir = script->getPropertyValue( "bin.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );

    string includeDirs = script->getPropertyValue( "include.dirs" );
    string libDirs = script->getPropertyValue( "lib.dirs" );
    string dllDirs = script->getPropertyValue( "dll.dirs" );

    string outputDefFile = script->getPropertyValue( "output.def.file" );
    string outImplibFile = script->getPropertyValue( "out.implib.file" );

    string defines = script->getPropertyValue( "defines" );
    string compiler = script->getPropertyValue( "compiler" );
    string exeFileName = script->getPropertyValue( "exe.file.name" );
    string dllFileName = script->getPropertyValue( "dll.file.name" );

    string compilerParams = script->getPropertyValue( "compiler.params" );
    string linkerParams = script->getPropertyValue( "linker.params" );

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

            executaTaskIfExists( "compile", manager );
        }

        if ( ok && isLink ) {
            cout << endl;
            if ( exeFileName == "" )
                throw proc_error( cmd, "A propriedade \"exe.file.name\" deve ter valor definido para linkagem." );

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

            executaTaskIfExists( "link", manager );
        }

        if ( ok ) {
            cout << "Compilacao e/ou linkagem executada(s) com sucesso!" << endl;
        } else {
            throw proc_error( cmd, "Houve falha na execucao de algum comando de compilacao ou linkagem." );
        }
    } else {
        throw proc_error( cmd, "Nao foi possivel ler o diretorio: \"" + srcDir + "\"" );
    }
}

void MainProc::appRecursiveDeleteFileOrDirectoryIfExists( string path ) {
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

void MainProc::appCopyFileOrDirectoryToBuild( string path, string buildDir ) {
    if ( !io::fileExists( path ) )
        throw runtime_error( "O arquivo ou pasta: \"" + path + "\" nao existe." );

    try {
        string bdir = ( buildDir == "" ? "." : buildDir );
        io::createDirectories( bdir );
        io::copyFileOrDirectory( path, bdir, true, true );

        cout << "Copiado: " << path << endl;
    } catch ( const io_error& e ) {
        throw runtime_error( "Nao foi possivel copiar o arquivo ou pasta: \"" + path + "\" para a pasta de build." );
    }
}

bool MainProc::isDefaultTask( string taskName ) {
    for( string name : defaultTasks )
        if ( name == taskName )
            return true;
    return false;
}

void MainProc::executaTaskIfExists( string taskName, ProcManager* manager ) {
    Task* task = manager->getMainScript()->getTask( taskName );
    if ( task != nullptr ) {
        cout << endl;

        int len = task->getCMDsLength();
        for( int i = 0; i < len; i++ ) {
            CMD* taskCMD = task->getCMDByIndex( i );
            Proc* proc = manager->getProc( taskCMD->getName() );
            if ( proc == nullptr )
                throw runtime_error( "Nenhum procedimento registrado para o comando: \"" + taskCMD->getName() + "\"" );

            proc->processa( taskCMD, manager );
        }
    }
}
