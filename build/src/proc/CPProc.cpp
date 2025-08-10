
#include "CPProc.h"
#include "../io/io.h"
#include "../io/filter/FileFilter.h"
#include "../util/strutil.h"

#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;

CPProc::CPProc( string cmdName ) : Proc( cmdName ) {}

void CPProc::processa( CMD* cmd, ProcManager* mgr ) {
    int alen = cmd->getArgsLength();
    if ( alen < 2 ) {
        stringstream ss;
        ss << "Numero de argumentos esperado igual a 2, encontrado " << alen;
        throw proc_error( cmd, ss.str() );
    }
    string src = cmd->getNotOpArg( 0 );
    string dest = cmd->getNotOpArg( 1 );

    io::createDirectories( dest );

    if ( io::isJokerCopyInPath( src ) ) {
        try {
            string srcDir = io::removeRecursiveJoker( src );
            srcDir = io::dirPath( srcDir );

            FileFilter* filter;
            string ext = io::extension( src );
            if ( ext != "" && src.find( "*." + ext ) != string::npos ) {
                ext = "." + ext;
                filter = io::by_ext_file_filter( ext );
            } else {
                filter = io::all_file_filter();
            }

            if ( src.find( "**" ) != string::npos ) {
                if ( strutil::endsWith( src, "*" ) )
                    throw proc_error( cmd, "Nao e possivel fazer copia com coringa no final e copia recursiva." );

                string replacePath = io::recursiveDirPathToReplace( src );
                replacePath = io::addSeparatorToDirIfNeed( replacePath );

                io::recursiveCopyFiles( srcDir, dest, replacePath, filter, true );
            } else {
                if ( strutil::endsWith( src, "*" ) ) {
                    string replacePath = io::dirPath( src );
                    io::recursiveCopyFiles( srcDir, dest, replacePath, filter, true );
                } else {
                    io::copyFiles( srcDir, dest, filter, true );
                }
            }
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Houve erro na copia recursiva dos arquivos.\nVerifique os caminhos da origem e do destino." );
        }
    } else {
        try {
            io::copyFileOrDirectory( src, dest, true );
        } catch ( const io_error& e ) {
            throw proc_error( cmd, "Houve erro na copia dos arquivos.\nVerifique os caminhos da origem e do destino." );
        }
    }
}
