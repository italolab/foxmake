
#include "ProcExec.h"
#include "CPProc.h"

const string configFileName = "exe.txt";

ProcExec::ProcExec() {
    mainInter = new MainInter();

    mainProc = new MainProc( "main" );

    map<string, Proc*>* mainSubProcsMap = new map<string, Proc*>();
    (*mainSubProcsMap)[ "cp" ] = new CPProc( "cp" );

    procsMapMap[ "main" ] = mainSubProcsMap;
}

void ProcExec::exec( int argc, char* argv[] ) {
    CMD* cmd = new CMD();
    try {
        cmd->interpreta( argc, argv );

        vector<string> cmdKeys = validSubCMDs( "main" );
        mainInter->interpreta( configFileName, cmdKeys );

        mainProc->processa( cmd, this );
    } catch ( const exception& e ) {
        cerr << "Erro: " << e.what() << endl;
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

MainProc* ProcExec::getMainProc() {
    return mainProc;
}

MainInter* ProcExec::getMainInter() {
    return mainInter;
}
