
#include "CPProc.h"
#include "../io/io.h"

#include <sstream>
#include <iostream>

using namespace std;

CPProc::CPProc( string cmdName ) : Proc( cmdName ) {}

void CPProc::processa( CMD* cmd, ProcManager* mgr ) {
    int alen = cmd->getArgsLength();
    if ( alen < 2 ) {
        stringstream ss;
        ss << "Erro em: \"" << cmd->getCMDStr() << "\"" << endl;
        ss << "Numero de argumentos esperado igual a 2, encontrado " << alen << endl;
        throw proc_error( ss.str() );
    }
    string src = cmd->getArg( 0 );
    string dest = cmd->getArg( 1 );

    bool srcRecursive;
    string srcDir = io::directoryPath( src, srcRecursive );
    string srcFile = io::fileOrDirName( src );

    string ext;
    bool copyByExt = false;

    if ( srcFile.length() > 2 ) {
        if ( srcFile[ 0 ] == '*' ) {
            if ( srcFile[ 1 ] == '.' ) {
                ext = srcFile.substr( 2, srcFile.length()-2 );
                copyByExt = true;
            } else {
                throw proc_error( "Erro em: \"" + cmd->getCMDStr() + "\"\nDeve haver um ponto após o coringa final do primeiro argumento." );
            }
        }
    }

    io::createDirectories( dest );

    if ( copyByExt ) {
        try {
            io::copyFilesByExt( srcDir, ext, dest, true );
        } catch ( const io_error& e ) {
            cout << e.what() << endl;
            throw proc_error( "Erro em: \"" + cmd->getCMDStr() + "\"\nHouve erro na copia recursiva dos arquivos." );
        }
    } else {
        try {
            io::copyFileOrDirectory( src, dest, true );
        } catch ( const io_error& e ) {
            throw proc_error( "Erro em: \"" + cmd->getCMDStr() + "\"\nHouve erro na copia dos arquivos." );
        }
    }
}
