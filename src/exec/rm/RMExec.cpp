
#include "RMExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../io/filter/FileFilter.h"
#include "../../util/strutil.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"

#include <sstream>

using std::stringstream;

void RMExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getArgManager()->isVerbose( cmd );

    if ( isVerbose )
        out << cmd->getCMDStr() << "\n";

    int alen = cmd->countNoOpArgs();
    if ( alen < 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string file = cmd->getNoOpArg( 0 );
    bool isRecursive = cmd->existsArg( "-r" );

    file = io::absoluteResolvePath( file );

    string fileName = io::fileOrDirName( file );

    FileFilter* filter = io::by_name_file_filter( fileName );

    int count;

    if ( isRecursive ) {
        try {            
            size_t i = fileName.find( '*' );
            if ( i != string::npos ) {                
                string dir = io::dirPath( file );
                count = io::recursiveDeleteFiles( dir, filter );         
            } else {
                count = io::recursiveDeleteFileOrDirectory( file );
            }
        } catch ( const io_error& e ) {
            messagebuilder b( errors::RECURSIVE_FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    } else {
        try {
            string dir = io::dirPath( file );

            bool deleted = io::deleteFiles( dir, filter );
            if ( deleted )
                count = 1;            
        } catch ( const io_error& e ) {
            messagebuilder b( errors::FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    }

    if ( isVerbose ) {
        messagebuilder b2( infos::FILES_AND_FOLDERS_DELETED );
        b2 << std::to_string( count );
        out << output::green( b2.str() ) << "\n";
    }
}
