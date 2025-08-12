
#include "ProcExec.h"
#include "CPProc.h"
#include "RMProc.h"
#include "CDProc.h"
#include "MKDirProc.h"
#include "EchoProc.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"

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

Proc* ProcExec::getProc( string cmdName ) {
    return procsMap[ cmdName ];
}

vector<string> ProcExec::validCMDNames() {
    vector<string> names;
    for( const auto& pair : procsMap )
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
