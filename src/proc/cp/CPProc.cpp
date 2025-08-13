
#include "CPProc.h"
#include "../../io/io.h"
#include "../../io/filter/FileFilter.h"
#include "../../util/strutil.h"

#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;

void CPProc::proc( CMD* cmd, void* mgr ) {
    int alen = cmd->countNoOpArgs();
    if ( alen != 2 ) {
        stringstream ss;
        ss << "Numero de argumentos esperado igual a 2, encontrado " << alen;
        throw proc_error( cmd, ss.str() );
    }
    string src = cmd->getNoOpArg( 0 );
    string dest = cmd->getNoOpArg( 1 );

    bool isRecursive = cmd->existsArg( "-r" );
    bool isOverwrite = !cmd->existsArg( "-no-overwrite" );

    if ( !io::fileExists( dest ) )
        throw proc_error( cmd, "O diretorio de destino nao existe: \"" + dest + "\"" );

    string replacePath = "";
    if ( src.find( '-' ) != string::npos ) {
        replacePath = io::recursiveDirPathToReplace( src );
        replacePath = io::addSeparatorToDirIfNeed( replacePath );
    }

    try {
        string fileName = io::fileOrDirName( src );

        bool isCopyAllFiles = false;
        bool isCopyByExt = false;
        if ( fileName.length() > 0 ) {
            isCopyAllFiles = ( fileName[ 0 ] == '*' );
            if ( isCopyAllFiles && fileName.length() > 1 )
                isCopyByExt = ( fileName[ 1 ] == '.' );
        }

        if ( isCopyAllFiles ) {
            string srcDir = io::removeRecursiveJoker( src );
            srcDir = io::dirPath( srcDir );

            if ( isCopyByExt ) {
                string ext = io::extension( src );
                if ( isRecursive ) {
                    io::recursiveCopyFiles( srcDir, dest, replacePath, io::by_ext_file_filter( ext ), isOverwrite );
                } else {
                    io::copyFiles( srcDir, dest, replacePath, io::by_ext_file_filter( ext ), isOverwrite );
                }
            } else {
                if ( isRecursive ) {
                    io::recursiveCopyFiles( srcDir, dest, replacePath, io::all_file_filter(), isOverwrite );
                } else {
                    io::copyFiles( srcDir, dest, replacePath, io::all_file_filter(), isOverwrite );
                }

            }
        } else {
            if ( !isRecursive && io::isDir( src ) && !io::isEmptyDir( src ) )
                throw proc_error( cmd, "Tentativa de copiar nao recursivamente uma pasta nao vazia." );

            io::copyFileOrDirectory( src, dest, isOverwrite, isRecursive );
        }
    } catch ( const io_error& e ) {
        throw proc_error( cmd, "Houve erro na copia do(s) arquivo(s).\nVerifique os caminhos da origem e do destino, se a copia e recursiva e com ou sem sobrescrita." );
    }
    cout << "CP Executado: \"" << cmd->getCMDStr() << "\"" << endl;
}
