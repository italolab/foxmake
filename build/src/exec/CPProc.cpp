
#include "CPProc.h"
#include "../util/ioutil.h"
#include "../util/utilexcept.h"

#include <sstream>
#include <iostream>

using namespace std;

void CPProc::processa( CMD* cmd, MainInter* config ) {
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
    string srcDir = directoryPath( src, srcRecursive );
    string srcFile = fileOrDirName( src );

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

    createDirectories( dest );

    if ( copyByExt ) {
        try {
            copyFilesByExt( srcDir, ext, dest, true );
        } catch ( const io_error& e ) {
            cout << e.what() << endl;
            throw proc_error( "Erro em: \"" + cmd->getCMDStr() + "\"\nHouve erro na copia recursiva dos arquivos." );
        }
    } else {
        try {
            copyFileOrDirectory( src, dest, true );
        } catch ( const io_error& e ) {
            throw proc_error( "Erro em: \"" + cmd->getCMDStr() + "\"\nHouve erro na copia dos arquivos." );
        }
    }
}
