
#include "CPExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../io/io.h"
#include "../../../io/filter/FileFilter.h"
#include "../../../util/strutil.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"

#include <sstream>

using std::string;
using std::stringstream;
using std::endl;

void CPExec::exec( ExecCMD* execCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* cmd = execCMD->getCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( cmd );

    if ( isVerbose )
        out << cmd->getCMDStr() << endl;

    int alen = execCMD->countNoOpArgs();
    if ( alen != 2 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "2" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }
    string src = execCMD->getNoOpArgByIndex( 0 );
    string dest = execCMD->getNoOpArgByIndex( 1 );

    bool isRecursive = cmd->existsArg( "-r" );
    bool isOverwrite = !cmd->existsArg( "-no-overwrite" );

    string src2 = io::path::absoluteResolvePath( src );
    string dest2 = io::path::absoluteResolvePath( dest );

    string replacePath = "";
    if ( src2.find( "**" ) != string::npos ) {
        replacePath = io::path::jokerJokerBeforePath( src2 );
    } else {
        
        replacePath = io::path::dirPath( src2 );
    }
    replacePath = io::path::addSeparatorIfNeed( replacePath );

    try {
        string fileName = io::path::fileOrDirName( src2 );

        size_t i = fileName.find( '*' );
        if ( i != string::npos ) {
            string srcDir = io::path::removeJokerJoker( src2 );
            srcDir = io::path::dirPath( srcDir );

            if ( !io::fileExists( srcDir ) ) {
                messagebuilder b( errors::SRC_DIRECTORY_NOT_EXISTS );
                b << srcDir;
                throw st_error( cmd, b.str() );
            }

            if ( !io::fileExists( dest2 ) || !io::isDir( dest2 ) ) {
                messagebuilder b( errors::DEST_DIRECTORY_NOT_EXISTS );
                b << dest2;
                throw st_error( cmd, b.str() );
            }

            FileFilter* filter = io::by_name_file_filter( fileName );
            io::copyFiles( srcDir, dest2, replacePath, filter, isOverwrite, isRecursive );                       
        } else {
            if ( !io::fileExists( src2 ) ) {
                messagebuilder b( errors::FILE_OR_FOLDER_NOT_FOUND );
                b << src2;
                throw st_error( cmd, b.str() );
            }

            if ( io::isDir( src2 ) ) {
                if ( !isRecursive && !io::isEmptyDir( src2 ) )
                    throw st_error( cmd, errors::TRY_RECURSIVE_COPY_OF_NOT_EMPTY_FOLDER );

                if ( io::isFile( dest2 ) ) {
                    messagebuilder b( errors::TRY_COPY_DIR_TO_FILE );
                    b << src2 << dest2;
                    throw st_error( cmd, b.str() );
                }

                if ( !io::isDir( dest2 ) ) {
                    string fname = io::path::fileOrDirName( dest2 );
                    dest2 = io::path::parentPath( dest2 );
                    dest2 = io::path::addSeparatorIfNeed( dest2 );
                    dest2 += fname;
                }
                
                io::copyDir( src2, dest2, isOverwrite, isRecursive );
            } else {
                if ( io::isDir( dest2 ) ) {
                    io::copyFileOrDir( src2, dest2, isOverwrite, isRecursive );
                } else {
                    io::copyFile( src2, dest2, isOverwrite );
                }
            }
        }
    } catch ( const io_error& e ) {
        throw st_error( cmd, errors::ERROR_IN_FILES_COPY );
    }    
}
