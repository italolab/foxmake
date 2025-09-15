
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

void RMExec::exec( ExecCMD* execCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    CMD* cmd = execCMD->getCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( cmd );

    if ( isVerbose )
        out << cmd->getCMDStr() << endl;

    int alen = execCMD->countNoOpArgs();
    if ( alen < 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string file = execCMD->getNoOpArgByIndex( 0 );
    bool isRecursive = cmd->existsArg( "-r" );

    file = io::path::absoluteResolvePath( file );

    string fileName = io::path::fileOrDirName( file );

    FileFilter* filter = io::by_name_file_filter( fileName );

    int count = 0;

    try {            
        size_t i = fileName.find( '*' );
        if ( i != string::npos ) {                
            string dir = io::path::dirPath( file );
            if ( io::fileExists( dir ) ) {
                if ( isRecursive ) {
                    count = io::deleteFiles( dir, filter, isRecursive );         
                } else {
                    if ( io::hasNoEmptyDir( dir, filter, isRecursive ) )
                        throw st_error( cmd, errors::TRY_DELETE_NO_RECURSIVE_NO_EMPTH_DIR );                        

                    count = io::deleteFiles( dir, filter, isRecursive ); 
                }
            } else {
                messagebuilder b( errors::FILE_OR_FOLDER_NOT_FOUND );
                b << dir;
                out << output::yellow( b.str() ) << endl;
            }
        } else {
            if ( io::fileExists( file ) ) {   
                count = io::deleteFileOrDir( file, isRecursive );
            } else {
                messagebuilder b( errors::FILE_OR_FOLDER_NOT_FOUND );
                b << file;
                out << output::yellow( b.str() ) << endl;
            }
        }
    } catch ( const io_error& e ) {
        out << e.what() << endl;
        messagebuilder b( isRecursive ? errors::RECURSIVE_FILE_OR_FOLDER_NOT_DELETED : errors::FILE_OR_FOLDER_NOT_DELETED );
        b << file;
        throw st_error( cmd, b.str() );
    }       

    if ( isVerbose ) {
        messagebuilder b2( infos::FILES_AND_FOLDERS_DELETED );
        b2 << std::to_string( count );
        out << output::green( b2.str() ) << endl;
    }
}
