
#include "MainProc.h"
#include "../ProcManager.h"
#include "../../darv/CMD.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/cppio.h"

#include <iostream>
#include <sstream>
#include <vector>

void MainProc::proc( CMD* cmd, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

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
            manager->executaTaskProc( "clean", cmd );

        if ( isCompile || isLink )
            compileAndLink( cmd, manager, isCompile, isLink );

        if ( isCopy )
            manager->executaTaskProc( "copy", cmd );

        vector<string> names = manager->getMainScript()->taskNames();
        for( string taskName : names )
            if ( !manager->isDefaultTask( taskName ) )
                manager->executaTaskIfExists( taskName );

        procCMDs( manager );
    } else {
        cout << "Nenhum comando informado." << endl;
    }
}

void MainProc::procCMDs( void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    MainScript* script = manager->getMainScript();
    int tam = script->getCMDsLength();

    if ( tam > 0 )
        cout << "\nEXECUTANDO COMANDOS" << endl;

    for( int i = 0; i < tam; i++ ) {
        CMD* cmd = script->getCMDByIndex( i );
        manager->executaCMDProc( cmd );
    }

    if ( tam > 0 )
        cout << "Comandos executados com sucesso." << endl;
}

void MainProc::compileAndLink( CMD* cmd, void* mgr, bool isCompile, bool isLink ) {
    ProcManager* manager = (ProcManager*)mgr;
    MainScript* script = manager->getMainScript();

    string srcDir = script->getPropertyValue( "src.dir" );
    string objDir = script->getPropertyValue( "obj.dir" );
    manager->reloadCPPFiles( srcDir );

    vector<CPPFile*>& cppFiles = manager->getCPPFiles();
    for( CPPFile* cppFile : cppFiles ) {
        string absFile = io::concatPaths( objDir, cppFile->objFileName );
        string dir = io::dirPath( absFile );
        io::createDirs( dir );
    }

    if ( isCompile )
        manager->executaTaskProc( "compile", cmd );
    if ( isLink )
        manager->executaTaskProc( "link", cmd );
}

