
#include "RMExec.h"
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

using std::stringstream;
using std::endl;

void RMExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( cmd );

    if ( isVerbose )
        out << cmd->getCMDStr() << endl;

    int alen = cmd->countNoOpArgs();
    if ( alen < 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string file = cmd->getNoOpArgByIndex( 0 );
    bool isRecursive = cmd->existsArg( "-r" );

    file = io::path::absoluteResolvePath( file );

    string fileName = io::path::fileOrDirName( file );

    FileFilter* filter = io::by_name_file_filter( fileName );

    int count;

    if ( isRecursive ) {
        try {            
            size_t i = fileName.find( '*' );
            if ( i != string::npos ) {                
                string dir = io::path::dirPath( file );
                count = io::deleteFiles( dir, filter, isRecursive );         
            } else {
                count = io::deleteFileOrDir( file, isRecursive );
            }
        } catch ( const io_error& e ) {
            messagebuilder b( errors::RECURSIVE_FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    } else {
        try {
            string dir = io::path::dirPath( file );

            if ( io::hasNoEmptyDir( dir, filter, isRecursive ) )
                throw st_error( cmd, errors::TRY_DELETE_NO_RECURSIVE_NO_EMPTH_DIR );                        

            count = io::deleteFiles( dir, filter, isRecursive );                        
        } catch ( const io_error& e ) {
            out << e.what() << endl;
            messagebuilder b( errors::FILE_OR_FOLDER_NOT_DELETED );
            b << file;
            throw st_error( cmd, b.str() );
        }
    }

    if ( isVerbose ) {
        messagebuilder b2( infos::FILES_AND_FOLDERS_DELETED );
        b2 << std::to_string( count );
        out << output::green( b2.str() ) << endl;
    }
}
