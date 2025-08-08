
#include "ProcExec.h"
#include "CPProc.h"
#include "../inter/block/it/FileIterator.h"

const string configFileName = "exe.txt";

ProcExec::ProcExec() {
    mainInter = new MainInter( this );

    mainProc = new MainProc( "main" );

    map<string, Proc*>* mainSubProcsMap = new map<string, Proc*>();
    (*mainSubProcsMap)[ "cp" ] = new CPProc( "cp" );

    procsMapMap[ "main" ] = mainSubProcsMap;

    this->mainCMDName = "main";
}

void ProcExec::exec( int argc, char* argv[] ) {
    try {
        CMDInter* cmd = new CMDInter();
        cmd->interpreta( argc, argv, 0 );


        FileIterator* it = new FileIterator( configFileName );
        mainInter->addVar( "main_config_file", configFileName );
        mainInter->interpreta( it );

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

vector<string> ProcExec::validMainCMDNames() {
    return validSubCMDs( mainCMDName );
}

MainProc* ProcExec::getMainProc() {
    return mainProc;
}

MainInter* ProcExec::getMainInter() {
    return mainInter;
}
