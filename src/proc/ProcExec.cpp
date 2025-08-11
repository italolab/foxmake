
#include "ProcExec.h"
#include "CPProc.h"
#include "CDProc.h"
#include "EchoProc.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"

const string configFileName = "exe.txt";

ProcExec::ProcExec() {
    mainScript = new MainScript();
    interManager = new InterManager( this );

    mainProc = new MainProc( "main" );

    procsMap[ "main" ] = mainProc;
    procsMap[ "cp" ] = new CPProc( "cp" );
    procsMap[ "cd" ] = new CDProc( "cd" );
    procsMap[ "echo" ] = new EchoProc( "echo" );
}

void ProcExec::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isOk() )
            throw runtime_error( "Erro: " + result->getErrorMsg() );

        CMD* cmd = (CMD*)result->getNo();

        mainScript->addLocalVar( "main_config_file", configFileName );
        mainScript->addLocalVar( "working_dir", shell::getWorkingDir() );

        InterResult* result2 = interManager->interpretsMainScript( mainScript, configFileName, 1 );
        if ( result2->isOk() ) {
            string wdir = mainScript->getLocalVar( "working_dir" )->getValue();
            cout << "Diretorio corrente: " << wdir << endl;

            mainProc->processa( cmd, this );
        } else {
            throw proc_error( result2->getNumberOfLines(), result2->getErrorMsg() );
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
