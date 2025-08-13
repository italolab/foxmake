
#include "MainProc.h"
#include "../ProcManager.h"
#include "../../darv/CMD.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/cppio.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;


void MainProc::proc( CMD* cmd, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    if ( cmd->countNoOpArgs() == 0 )
        throw runtime_error( "E necessario informar ao menos uma tarefa como argumento." );

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

    executaNoDefaultTasks( manager );
    executaCMDs( manager );
}

void MainProc::executaNoDefaultTasks( void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;

    vector<string> names = manager->getMainScript()->taskNames();
    for( string taskName : names )
        if ( !manager->isDefaultTask( taskName ) )
            manager->executaTaskIfExists( taskName );
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
        manager->executaTaskProc( "compileall", cmd );
    if ( isLink )
        manager->executaTaskProc( "link", cmd );
}

void MainProc::executaCMDs( void* mgr ) {
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
