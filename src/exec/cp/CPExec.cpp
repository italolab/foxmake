
#include "CPExec.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../io/filter/FileFilter.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"

#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;

void CPExec::exec( CMD* cmd, void* mgr ) {
    int alen = cmd->countNoOpArgs();
    if ( alen != 2 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "2" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }
    string src = cmd->getNoOpArg( 0 );
    string dest = cmd->getNoOpArg( 1 );

    bool isRecursive = cmd->existsArg( "-r" );
    bool isOverwrite = !cmd->existsArg( "-no-overwrite" );

    if ( !io::fileExists( dest ) ) {
        messagebuilder b( errors::DEST_DIRECTORY_NOT_EXISTS );
        b << dest;
        throw st_error( cmd, b.str() );
    }

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
                throw st_error( cmd, errors::TRY_RECURSIVE_COPY_OF_NOT_EMPTY_FOLDER );

            io::copyFileOrDirectory( src, dest, isOverwrite, isRecursive );
        }
    } catch ( const io_error& e ) {
        throw st_error( cmd, errors::ERROR_IN_FILES_COPY );
    }

    messagebuilder b ( infos::EXECUTED_CMD );
    b << cmd->getCMDStr();
    cout << b.str() << endl;
}
