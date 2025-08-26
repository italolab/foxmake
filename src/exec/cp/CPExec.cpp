
#include "CPExec.h"
#include "../ExecManager.h"
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
    ExecManager* manager = (ExecManager*)mgr;

    bool isVerbose = manager->getArgManager()->isVerbose( cmd );

    if ( isVerbose )
        cout << cmd->getCMDStr() << endl;

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

    string src2 = io::absoluteResolvePath( src );
    string dest2 = io::absoluteResolvePath( dest );

    string withoutInitTwoDotsAndSlashSrc = io::removeInitTwoDotsAndSlash( src );    

    if ( !io::fileExists( dest2 ) ) {
        messagebuilder b( errors::DEST_DIRECTORY_NOT_EXISTS );
        b << dest2;
        throw st_error( cmd, b.str() );
    }

    string replacePath = "";
    if ( src2.find( "**" ) != string::npos ) {
        replacePath = io::recursiveDirPathToReplace( src2 );
    } else {
        replacePath = io::dirPath( src2 );
    }
    replacePath = io::addSeparatorToDirIfNeed( replacePath );

    try {
        string fileName = io::fileOrDirName( src2 );

        string srcDir = io::removeRecursiveJoker( src2 );
        srcDir = io::dirPath( srcDir );
                
        FileFilter* filter = io::by_name_file_filter( fileName );

        size_t i = fileName.find( '*' );
        if ( i != string::npos ) {
            if ( isRecursive ) {
                io::recursiveCopyFiles( srcDir, dest2, replacePath, filter, isOverwrite );
            } else {
                io::copyFiles( srcDir, dest2, replacePath, filter, isOverwrite );
            }            
        } else {
            if ( !isRecursive && io::isDir( src2 ) && !io::isEmptyDir( src2 ) )
                throw st_error( cmd, errors::TRY_RECURSIVE_COPY_OF_NOT_EMPTY_FOLDER );

            io::copyFileOrDirectory( src2, dest2, isOverwrite, isRecursive );
        }
    } catch ( const io_error& e ) {
        throw st_error( cmd, errors::ERROR_IN_FILES_COPY );
    }    
}
