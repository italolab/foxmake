
#include "MKDirExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"

#include <sstream>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

void MKDirExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    bool isVerbose = manager->isVerbose( cmd );

    int alen = cmd->countNoOpArgs();
    if ( alen < 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string dir = cmd->getNoOpArg( 0 );
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
                cerr << b.str() << endl;
            }
        } catch ( const io_error& e ) {
            throw st_error( cmd, errors::DIRECTORY_NOT_CREATED_2 );
        }
    }

    if ( isVerbose ) {
        messagebuilder b( infos::EXECUTED_CMD );
        b << cmd->getCMDStr();
        cout << b.str() << endl;
    }
}
