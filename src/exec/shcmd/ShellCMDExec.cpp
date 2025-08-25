
#include "ShellCMDExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../shell/shell.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

#include <iostream>

using std::cout;
using std::endl;

void ShellCMDExec::exec( ShellCMD* shellCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    string cmdstr = shellCMD->getCMDStr();
    bool isVerbose = manager->isVerbose( shellCMD );
    bool isShowCMDOutput = manager->isShowCMDOutput( shellCMD );

    Shell* shell = new Shell();
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );
    shell->pushCommand( consts::SHELL_EXE + " " + cmdstr );

    int result = shell->executa();
    if ( result != 0 ) {
        messagebuilder b( errors::SHELL_CMD_NOT_EXECUTED );
        b << std::to_string( result );
        throw st_error( shellCMD, b.str() );
    }

    delete shell;
}
