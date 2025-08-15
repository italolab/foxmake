
#include "MainProc.h"
#include "../ProcManager.h"
#include "../../darv/CMD.h"
#include "../../inter/InterResult.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"

#include "../../consts.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;


void MainProc::proc( CMD* mainCMD, void* mgr ) {
    ProcManager* manager = (ProcManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();

    mainScript->putLocalVar( "main_config_file", consts::DEFAULT_SETTINGS_FILE_NAME );
    mainScript->putLocalVar( "working_dir", shell::getWorkingDir() );

    InterResult* result2 = interManager->interpretsMainScript( mainScript, consts::DEFAULT_SETTINGS_FILE_NAME, 1 );
    if ( !result2->isInterpreted() )
        throw proc_error( result2 );

    string wdir = mainScript->getLocalVar( "working_dir" )->getValue();
    cout << "Diretorio corrente: " << wdir << endl;

    if ( mainCMD->countNoOpArgs() == 0 )
        throw proc_error( mainCMD, "E necessario informar ao menos uma tarefa como argumento." );

    bool isClean = mainCMD->existsArg( tasks::CLEAN );
    bool isCompile = mainCMD->existsArg( tasks::COMPILE );
    bool isLink = mainCMD->existsArg( tasks::LINK );
    bool isCopy = mainCMD->existsArg( tasks::COPY );
    bool isBuild = mainCMD->existsArg( tasks::BUILD );

    bool isBuildAll = mainCMD->existsArg( tasks::BUILDALL );

    if ( isBuild || isBuildAll ) {
        isClean = true;
        isCompile = true;
        isLink = true;
        isCopy = true;
    }

    if ( isClean )
        manager->executaTaskProc( tasks::CLEAN, mainCMD );

    if ( isCompile || isLink )
        compileAndLink( mainCMD, manager, isCompile, isLink );

    if ( isCopy )
        manager->executaTaskProc( tasks::COPY, mainCMD );

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
void MainProc::compileAndLink( CMD* mainCMD, void* mgr, bool isCompile, bool isLink ) {
    ProcManager* manager = (ProcManager*)mgr;
    MainScript* script = manager->getMainScript();

    string srcDir = script->getPropertyValue( props::SRC_DIR );
    string objDir = script->getPropertyValue( props::OBJ_DIR );

    if ( !io::fileExists( srcDir ) )
        throw proc_error( mainCMD, "Diretorio de codigos fonte nao encontrado.\nVerifique a propriedade \"" + props::SRC_DIR + "\"" );

    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    bool ok = sourceCodeManager->recursiveProcFiles( srcDir );
    if ( !ok )
        throw proc_error( mainCMD, "Houve algum problema de leitura dos arquivos de codigo fonte." );

    vector<CodeInfo*> sourceCodeInfos = sourceCodeManager->sourceCodeInfos();
    for( CodeInfo* info : sourceCodeInfos ) {
        string absFile = io::concatPaths( objDir, info->objFilePath );
        string dir = io::dirPath( absFile );
        io::createDirs( dir );
    }

    if ( isCompile )
        manager->executaTaskProc( tasks::COMPILEALL, mainCMD );
    if ( isLink )
        manager->executaTaskProc( tasks::LINK, mainCMD );
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
