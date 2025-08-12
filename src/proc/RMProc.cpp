
#include "RMProc.h"
#include "../io/io.h"
#include "../util/strutil.h"

#include <sstream>

void RMProc::processa( CMD* cmd, ProcManager* manager ) {
    int alen = cmd->countNotOpArgs();
    if ( alen < 1 ) {
        stringstream ss;
        ss << "Numero de argumentos esperado igual a 1, encontrado " << alen;
        throw proc_error( cmd, ss.str() );
    }

    string file = cmd->getNotOpArg( 0 );
    bool isRecursive = cmd->existsArg( "-r" );

    string fileName = io::fileOrDirName( file );

    if ( isRecursive ) {
        try {
            bool isDeleteAllFiles = false;
            bool isDeleteByExt = false;
            if ( fileName.length() > 0 ) {
                isDeleteAllFiles = ( fileName[ 0 ] == '*' );
                if ( isDeleteAllFiles && fileName.length() > 1 )
                    isDeleteByExt = ( fileName[ 1 ] == '.' );
            }

            file = io::removeDirContentJoker( file );

            int count;
            if ( isDeleteAllFiles ) {
                string dir = io::dirPath( file );
                if ( isDeleteByExt ) {
                    string ext = io::extension( fileName );
                    count = io::recursiveDeleteFilesOnly( dir, io::by_ext_file_filter( ext ) );
                } else {
                    count = io::recursiveDeleteDirectoryContent( dir );
                }
            } else {
                count = io::recursiveDeleteFileOrDirectory( file );
            }

            if ( count == 0 )
                throw proc_error( cmd, "Arquivo ou pasta nao existe." );
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Houve um erro na delecao do arquivo ou pasta." );
        }
    } else {
        try {
            bool deleted = io::deleteFileOrDirectory( file );
            if ( !deleted )
                throw proc_error( cmd, "Verifique se o arquivo ou pasta existe." );
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Se o arquivo e um diretorio, verifique se esta vasio ou tente remover recursivamente." );
        }
    }

    cout << "RM Executado: " << cmd->getCMDStr() << endl;
}
