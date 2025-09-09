
#include "CallExec.h"
#include "../ExecManager.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

void CallExec::exec( CallCMD* callCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    Proc* proc = callCMD->getProc();
    if ( proc == nullptr ) {
        messagebuilder b ( errors::runtime::NULL_PROC );
        b << __func__;
        throw runtime_error( b.str() );
    }
    manager->executeBlockStatements( proc );
}