
#include "ProcExec.h"
#include "cp/CPProc.h"
#include "rm/RMProc.h"
#include "cd/CDProc.h"
#include "mkdir/MKDirProc.h"
#include "echo/EchoProc.h"
#include "main/CleanTaskProc.h"
#include "main/CompileAllTaskProc.h"
#include "main/LinkTaskProc.h"
#include "main/CopyTaskProc.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"
#include "../io/cppio.h"

#include "../consts.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

ProcExec::ProcExec() {
    mainScript = new MainScript();
    interManager = new InterManager( this );

    mainProc = new MainProc();

    procsMap[ cmds::CP ] = new CPProc();
    procsMap[ cmds::RM ] = new RMProc();
    procsMap[ cmds::CD ] = new CDProc();
    procsMap[ cmds::MKDIR ] = new MKDirProc();
    procsMap[ cmds::ECHO ] = new EchoProc();

    taskProcsMap[ tasks::CLEAN ] = new CleanTaskProc();
    taskProcsMap[ tasks::COMPILEALL ] = new CompileAllTaskProc();
    taskProcsMap[ tasks::LINK ] = new LinkTaskProc();
    taskProcsMap[ tasks::COPY ] = new CopyTaskProc();
}

void ProcExec::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isInterpreted() )
            throw runtime_error( "Erro em: \"" + result->getLine() + "\"\n" + result->getErrorMsg() );

        CMD* cmd = (CMD*)result->getStatement();

        mainScript->putLocalVar( "main_config_file", consts::DEFAULT_SETTINGS_FILE_NAME );
        mainScript->putLocalVar( "working_dir", shell::getWorkingDir() );

        InterResult* result2 = interManager->interpretsMainScript( mainScript, consts::DEFAULT_SETTINGS_FILE_NAME, 1 );
        if ( !result2->isInterpreted() )
            throw proc_error( result2 );

        string wdir = mainScript->getLocalVar( "working_dir" )->getValue();
        cout << "Diretorio corrente: " << wdir << endl;

        mainProc->proc( cmd, this );
    } catch ( const taskproc_error& e ) {
        cerr << e.message() << endl;
    } catch ( const proc_error& e ) {
        cerr << e.message() << endl;
    } catch ( const exception& e ) {
        cerr << e.what() << endl;
    }
}

void ProcExec::reloadCPPFiles( string srcDir ) {
    cppFilesVect.clear();

    bool ok = cppio::recursiveProcSrcFiles( srcDir, cppFilesVect );
    if ( !ok )
        throw runtime_error( "Nao foi possivel ler o diretorio de fontes do projeto: \"" + srcDir + "\"" );
}

void ProcExec::executaCMDProc( CMD* cmd ) {
    Proc* proc = procsMap[ cmd->getName() ];
    if ( proc == nullptr )
        throw runtime_error( "Procedimento de comando nao encontrado pelo nome: \"" + cmd->getName() + "\"" );
    proc->proc( cmd, this );
}

void ProcExec::executaTaskProc( string taskName, CMD* mainCMD ) {
    TaskProc* proc = taskProcsMap[ taskName ];
    if ( proc == nullptr )
        throw runtime_error( "Procedimento de tarefa nao encontrado pelo nome: \"" + taskName + "\"" );
    proc->proc( mainCMD, this );
}

void ProcExec::executaTaskIfExists( string taskName ) {
    Task* task = mainScript->getTask( taskName );
    if ( task != nullptr ) {
        cout << endl;

        int len = task->getCMDsLength();
        for( int i = 0; i < len; i++ ) {
            CMD* taskCMD = task->getCMDByIndex( i );
            this->executaCMDProc( taskCMD );
        }
    }
}

bool ProcExec::isDefaultTask( string taskName ) {
    vector<string> defaultTasks = registeredTaskProcNames();
    for( string name : defaultTasks )
        if ( name == taskName )
            return true;
    return false;
}

vector<CPPFile*>& ProcExec::getCPPFiles() {
    return cppFilesVect;
}

vector<string> ProcExec::validCMDNames() {
    vector<string> names;
    for( const auto& pair : procsMap )
        names.push_back( pair.first );
    return names;
}

vector<string> ProcExec::registeredTaskProcNames() {
    vector<string> names;
    for( const auto& pair : taskProcsMap )
        names.push_back( pair.first );
    return names;
}

vector<string> ProcExec::validPropNames() {
    return props::VALID_NAMES;
}

MainProc* ProcExec::getMainProc() {
    return mainProc;
}

MainScript* ProcExec::getMainScript() {
    return mainScript;
}

InterManager* ProcExec::getInterManager() {
    return interManager;
}
