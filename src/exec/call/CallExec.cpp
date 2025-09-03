
#include "CallExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

void CallExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
        
    int alen = cmd->countNoOpArgs();
    if ( alen != 1 ) {
        messagebuilder b;
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string procName = cmd->getNoOpArgByIndex( 0 );

    bool exists = manager->executeProc( procName );
    
    if ( !exists ) {
        messagebuilder b( errors::PROC_NOT_FOUND );
        b << procName;
        throw st_error( cmd, b.str() );
    }
}