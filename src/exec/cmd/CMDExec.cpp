
#include "CMDExec.h"
#include "../ExecManager.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

CMDExec::CMDExec() {
    cpExec = new CPExec();
    rmExec = new RMExec();
    cdExec = new CDExec();
    mkdirExec = new MKDirExec();
    echoExec = new EchoExec();
}

CMDExec::~CMDExec() {
    delete cdExec;
    delete cpExec;
    delete rmExec;
    delete echoExec;
    delete mkdirExec;
}

void CMDExec::exec( CMD* cmd, void* mgr ) {
    string cmdName = cmd->getName();
    if ( cmdName == "cd" ) {
        cdExec->exec( cmd, mgr );
    } else if ( cmdName == "cp" ) {
        cpExec->exec( cmd, mgr );
    } else if ( cmdName == "rm" ) {
        rmExec->exec( cmd, mgr );
    } else if ( cmdName == "echo" ) {
        echoExec->exec( cmd, mgr );
    } else if ( cmdName == "mkdir" ) {
        mkdirExec->exec( cmd, mgr );
    } else {
        messagebuilder b( errors::runtime::CMD_EXECUTOR_NOT_FOUND );
        b << cmd->getName();
        throw runtime_error( b.str() );
    }
}