
#include "CDExec.h"
#include "../stexcept.h"
#include "../ExecManager.h"
#include "../../darv/Var.h"
#include "../../shell/shell.h"
#include "../../io/io.h"
#include "../../msg/messagebuilder.h"

#include "../../consts.h"
#include "../../error_messages.h"
#include "../../info_messages.h"

#include <sstream>
#include <iostream>

using std::stringstream;
using std::cout;
using std::endl;

void CDExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();

    bool isVerbose = manager->getArgManager()->isVerbose( cmd );
    
    int alen = cmd->countNoOpArgs();
    if ( alen != 1 ) {
        messagebuilder b;
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string newDir = cmd->getNoOpArg( 0 );

    if ( !io::fileExists( newDir ) )
        throw st_error( cmd, errors::DIRECTORY_NOT_FOUND );

    if ( !io::isDir( newDir ) )
        throw st_error( cmd, errors::INFORMED_PATH_IS_NOT_A_DIRECTORY );

    bool ok = shell::setWorkingDir( newDir );
    if ( !ok )
        throw st_error( cmd, errors::CURRENT_DIRECTORY_NOT_CHANGED );

    Var* var = script->getLocalVar( "working_dir" );
    if ( var == nullptr )
        throw st_error( cmd, errors::WORKDIR_VAR_NOT_FOUND );

    var->setValue( shell::getWorkingDir() );

    if ( isVerbose ) {
        messagebuilder b( infos::NEW_CURRENT_DIRECTORY );
        b << var->getValue();
        cout << b.str() << endl;
    }
}
