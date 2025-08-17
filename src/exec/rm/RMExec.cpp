
#include "RMExec.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"

#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::stringstream;

void RMExec::exec( CMD* cmd, void* mgr ) {
    int alen = cmd->countNoOpArgs();
    if ( alen < 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string file = cmd->getNoOpArg( 0 );
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

            if ( count == 0 ) {
                messagebuilder b( errors::RECURSIVE_FILE_OR_FOLDER_NOT_DELETED );
                b << file;
                throw st_error( cmd, b.str() );
            }
        } catch ( const io_error& e ) {
            messagebuilder b( errors::RECURSIVE_FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    } else {
        try {
            bool deleted = io::deleteFileOrDirectory( file );
            if ( !deleted ) {
                messagebuilder b( errors::FILE_OR_FOLDER_NOT_DELETED );
                b << file;
                throw st_error( cmd, b.str() );
            }
        } catch ( const io_error& e ) {
            messagebuilder b( errors::FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    }

    messagebuilder b( infos::EXECUTED_CMD );
    b << cmd->getCMDStr();
    cout << b.str() << endl;
}
