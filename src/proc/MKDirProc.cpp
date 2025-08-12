
#include "MKDirProc.h"
#include "../io/io.h"

#include <sstream>

void MKDirProc::processa( CMD* cmd, ProcManager* manager ) {
    int alen = cmd->countNoOpArgs();
    if ( alen < 1 ) {
        stringstream ss;
        ss << "Numero de argumentos esperado igual a 1, encontrado " << alen;
        throw proc_error( cmd, ss.str() );
    }

    string dir = cmd->getNoOpArg( 0 );
    bool isCreateParents = cmd->existsArg( "-p" );

    bool ok;
    if ( isCreateParents ) {
        try {
            io::createDirs( dir );
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Nao foi possivel criar os diretorios do caminho informado." );
        }
    } else {
        try {
            ok = io::createDir( dir );
            if ( !ok )
                cerr << "Pasta ja existe: " << dir << endl;
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Nao foi possivel criar o diretorio. \nVerifique se o diretorio onde quer criar o novo diretorio existe." );
        }
    }

    cout << "MKDIR Executado: " << cmd->getCMDStr() << endl;
}
