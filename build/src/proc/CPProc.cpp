
#include "CPProc.h"
#include "../io/io.h"
#include "../io/filter/FileFilter.h"
#include "../util/strutil.h"

#include <sstream>
#include <iostream>

using namespace std;

CPProc::CPProc( string cmdName ) : Proc( cmdName ) {}

void CPProc::processa( CMDInter* inter, ProcManager* mgr ) {
    int alen = inter->getArgsLength();
    if ( alen < 2 ) {
        stringstream ss;
        ss << "Linha(" << inter->getLineNumber() << "): numero de argumentos esperado igual a 2, encontrado " << alen << endl;
        ss << "Erro em: \"" << inter->getCMDStr() << "\"";
        throw proc_error( ss.str() );
    }
    string src = inter->getNotOpArg( 0 );
    string dest = inter->getNotOpArg( 1 );

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
                if ( strutil::endsWith( src, "*" ) ) {
                    stringstream ss;
                    ss << "Linha(" << inter->getLineNumber() << ": nao e possivel fazer copia com coringa no final e copia recursiva." << endl;
                    ss << "Erro em: \"" + inter->getCMDStr() << "\"";
                    throw proc_error( ss.str() );
                }

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
            stringstream ss;
            ss << "Linha(" << inter->getLineNumber() << ": houve erro na copia recursiva dos arquivos." << endl;
            ss << "Erro em: \"" + inter->getCMDStr() << "\"";
            throw proc_error( ss.str() );
        }
    } else {
        try {
            io::copyFileOrDirectory( src, dest, true );
        } catch ( const io_error& e ) {
            stringstream ss;
            ss << "Linha(" << inter->getLineNumber() << ": houve erro na copia dos arquivos." << endl;
            ss << "Erro em: \"" + inter->getCMDStr() << "\"";
            throw proc_error( ss.str() );
        }
    }
}
