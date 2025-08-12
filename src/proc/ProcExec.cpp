
#include "ProcExec.h"
#include "CPProc.h"
#include "RMProc.h"
#include "CDProc.h"
#include "MKDirProc.h"
#include "EchoProc.h"
#include "task/CleanTaskProc.h"
#include "task/CompileTaskProc.h"
#include "task/LinkTaskProc.h"
#include "task/CopyTaskProc.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"
#include "../io/cppio.h"

const string configFileName = "exe.txt";

ProcExec::ProcExec() {
    mainScript = new MainScript();
    interManager = new InterManager( this );

    mainProc = new MainProc();

    procsMap[ "cp" ] = new CPProc();
    procsMap[ "rm" ] = new RMProc();
    procsMap[ "cd" ] = new CDProc();
    procsMap[ "mkdir" ] = new MKDirProc();
    procsMap[ "echo" ] = new EchoProc();

    taskProcsMap[ "clean" ] = new CleanTaskProc();
    taskProcsMap[ "compile" ] = new CompileTaskProc();
    taskProcsMap[ "link" ] = new LinkTaskProc();
    taskProcsMap[ "copy" ] = new CopyTaskProc();
}

void ProcExec::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isInterpreted() )
            throw runtime_error( "Erro em: \"" + result->getLine() + "\"\n" + result->getErrorMsg() );

        CMD* cmd = (CMD*)result->getNo();

        mainScript->putLocalVar( "main_config_file", configFileName );
        mainScript->putLocalVar( "working_dir", shell::getWorkingDir() );

        InterResult* result2 = interManager->interpretsMainScript( mainScript, configFileName, 1 );
        if ( result2->isInterpreted() ) {
            string wdir = mainScript->getLocalVar( "working_dir" )->getValue();
            cout << "Diretorio corrente: " << wdir << endl;

            mainProc->processa( cmd, this );
        } else {
            throw proc_error( result2 );
        }
    } catch ( const proc_error& e ) {
        cerr << e.message() << endl;
    } catch ( const exception& e ) {
        cerr << e.what() << endl;
    }
}

void ProcExec::reloadCPPFiles( string srcDir ) {
    bool ok = cppio::recursiveProcSrcFiles( srcDir, cppFilesVect );
    if ( !ok )
        throw runtime_error( "Nao foi possivel ler o diretorio de fontes do projeto: \"" + srcDir + "\"" );
}

void ProcExec::executaTaskProc( string taskName, CMD* mainCMD ) {
    Proc* proc = this->getTaskProc( taskName );
    if ( proc == nullptr )
        throw runtime_error( "Procedimento de tarefa nao encontrado pelo nome: \"" + taskName + "\"" );
    proc->processa( mainCMD, this );
}

void ProcExec::executaTaskIfExists( string taskName ) {
    Task* task = mainScript->getTask( taskName );
    if ( task != nullptr ) {
        cout << endl;

        int len = task->getCMDsLength();
        for( int i = 0; i < len; i++ ) {
            CMD* taskCMD = task->getCMDByIndex( i );
            Proc* proc = this->getProc( taskCMD->getName() );
            if ( proc == nullptr )
                throw runtime_error( "Nenhum procedimento registrado para o comando: \"" + taskCMD->getName() + "\"" );

            proc->processa( taskCMD, this );
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

Proc* ProcExec::getProc( string cmdName ) {
    return procsMap[ cmdName ];
}

Proc* ProcExec::getTaskProc( string taskName ) {
    return taskProcsMap[ taskName ];
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

MainProc* ProcExec::getMainProc() {
    return mainProc;
}

MainScript* ProcExec::getMainScript() {
    return mainScript;
}

InterManager* ProcExec::getInterManager() {
    return interManager;
}
