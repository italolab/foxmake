
#include "MainExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/CMD.h"
#include "../../inter/InterResult.h"
#include "../../shell/shell.h"
#include "../../util/strutil.h"
#include "../../io/io.h"
#include "../../io/SourceCodeManager.h"

#include "../../consts.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;

void MainExec::exec( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();
    MainScript* mainScript = manager->getMainScript();

    if ( mainCMD->countNoOpArgs() == 0 )
        throw st_error( mainCMD, "E necessario informar ao menos uma tarefa como argumento." );

    string settingsFile = mainCMD->getPropertyValue( "--settings-file" );
    if ( settingsFile == "" )
        settingsFile = consts::DEFAULT_SETTINGS_FILE_NAME;

    settingsFile = io::absolutePath( settingsFile );
    cout << "Arquivo de configuracao: \"" << settingsFile << endl;

    if ( !io::fileExists( settingsFile ) )
        throw st_error( mainCMD, "Arquivo de configuracoes nao encontrado." );

    string workingDir = io::dirPath( settingsFile );
    shell::setWorkingDir( workingDir );

    mainScript->putLocalVar( "main_config_file", settingsFile );
    mainScript->putLocalVar( "working_dir", shell::getWorkingDir() );

    InterResult* result = interManager->interpretsMainScript( mainScript, settingsFile, 1 );
    if ( !result->isInterpreted() )
        throw st_error( result );

    delete result;

    string wdir = mainScript->getLocalVar( "working_dir" )->getValue();
    cout << "Diretorio corrente: \"" << wdir << "\"" << endl;

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

    if ( isCompile || isLink )
        this->genSourceAndHeaderInfos( mainCMD, manager );

    if ( isClean )
        manager->executaTask( tasks::CLEAN, mainCMD );
    if ( isCompile )
        manager->executaTask( tasks::COMPILE, mainCMD );
    if ( isLink )
        manager->executaTask( tasks::LINK, mainCMD );
    if ( isCopy )
        manager->executaTask( tasks::COPY, mainCMD );

    this->executaNoDefaultTasks( manager );
    this->executaStatements( manager );
}

void MainExec::genSourceAndHeaderInfos( CMD* mainCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    SourceCodeManager* sourceCodeManager = manager->getSourceCodeManager();

    MainScript* script = manager->getMainScript();

    string srcDir = script->getPropertyValue( props::SRC_DIR );

    if ( srcDir != "" && !io::fileExists( srcDir ) ) {
        string src = io::absolutePath( srcDir );
        stringstream ss;
        ss << "Diretorio de codigos fonte nao encontrado: \"" << src << "\"" << endl;
        ss << "Verifique a propriedade \"" << props::SRC_DIR + "\"";
        throw st_error( mainCMD, ss.str() );
    }

    srcDir = io::absolutePath( srcDir );
    cout << "SRC DIR=\"" << srcDir << "\"" << endl;

    bool ok = sourceCodeManager->recursiveProcFiles( srcDir );
    if ( !ok ) {
        stringstream ss;
        ss << "Houve algum erro na leitura dos arquivos de codigo fonte.";
        throw st_error( mainCMD, ss.str() );
    }
}

void MainExec::executaNoDefaultTasks( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    vector<string> names = manager->getMainScript()->taskNames();
    for( string taskName : names ) {
        if ( !manager->isDefaultTask( taskName ) ) {
            cout << "\nEXECUTANDO " << taskName << "..." << endl;
            manager->executaTaskIfExists( taskName );
        }
    }
}

void MainExec::executaStatements( void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    MainScript* script = manager->getMainScript();
    int tam = script->getStatementsLength();

    if ( tam > 0 )
        cout << "\nEXECUTANDO INSTRUCOES" << endl;

    for( int i = 0; i < tam; i++ ) {
        Statement* st = script->getStatementByIndex( i );
        manager->executaStatement( st );
    }

    if ( tam > 0 )
        cout << "Instrucoes executadas com sucesso." << endl;
}
