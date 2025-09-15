
#include "MKDirExec.h"
#include "../../ExecManager.h"
#include "../../stexcept.h"
#include "../../../io/io.h"
#include "../../../msg/messagebuilder.h"

#include "../../../error_messages.h"
#include "../../../info_messages.h"

#include <sstream>

using std::stringstream;
using std::endl;

void MKDirExec::exec( ExecCMD* execCMD, void* mgr ) {
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

    string dir = execCMD->getNoOpArgByIndex( 0 );
    bool isCreateParents = cmd->existsArg( "-p" );

    bool ok;
    if ( isCreateParents ) {
        try {
            io::createDirs( dir );
        } catch ( const io_error& e ) {
            throw st_error( cmd, errors::DIRECTORIES_NOT_CREATED );
        }
    } else {
        try {
            ok = io::createDir( dir );
            if ( !ok && isVerbose ) {
                messagebuilder b( errors::FOLDER_ALREADY_EXISTS );
                b << dir;
                out << output::yellow( b.str() ) << endl;
            }
        } catch ( const io_error& e ) {
            throw st_error( cmd, errors::DIRECTORY_NOT_CREATED_2 );
        }
    }
}
