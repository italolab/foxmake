
#include "ProcExec.h"
#include "CPProc.h"
#include "CDProc.h"
#include "../inter/InterResult.h"
#include "../shell/shell.h"

const string configFileName = "exe.txt";

ProcExec::ProcExec() {
    mainScript = nullptr;
    interManager = new InterManager( this );

    mainProc = new MainProc( "main" );

    map<string, Proc*>* mainSubProcsMap = new map<string, Proc*>();
    (*mainSubProcsMap)[ "cp" ] = new CPProc( "cp" );
    (*mainSubProcsMap)[ "cd" ] = new CDProc( "cd" );

    procsMapMap[ "main" ] = mainSubProcsMap;

    this->mainCMDName = "main";
}

void ProcExec::exec( int argc, char* argv[] ) {
    try {
        InterResult* result = interManager->interpretsMainCMD( argc, argv );
        if ( !result->isOk() )
            throw runtime_error( "Erro: " + result->getErrorMsg() );

        CMD* cmd = (CMD*)result->getNo();

        InterResult* result2 = interManager->interpretsMainScript( configFileName, 1 );
        if ( result2->isOk() ) {
            mainScript = (MainScript*)result2->getNo();
            mainScript->addLocalVar( "main_config_file", configFileName );
            mainScript->addLocalVar( "working_dir", shell::getWorkingDir() );

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

vector<string> ProcExec::validSubCMDs( string cmdName ) {
    vector<string> keys;

    map<string, Proc*>* pmap = getProcsMap( cmdName );
    for( const auto& pair : *pmap )
        keys.push_back( pair.first );
    return keys;
}

Proc* ProcExec::getProc( string cmdName, string subCmdName ) {
    map<string, Proc*>* pmap = getProcsMap( cmdName );
    return (*pmap)[ subCmdName ];
}

map<string, Proc*>* ProcExec::getProcsMap( string cmdName ) {
    map<string, Proc*>* pmap = procsMapMap[ cmdName ];
    if ( pmap == nullptr )
        throw runtime_error( "Nome de cmd (Proc) invalido: \"" + cmdName + "\"" );
    return pmap;
}

vector<string> ProcExec::validMainCMDNames() {
    return validSubCMDs( mainCMDName );
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
