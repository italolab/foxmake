
#include "ShellCMDExec.h"
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
    string cmdstr = shellCMD->getCMDStr();

    Shell* shell = new Shell();
    shell->pushCommand( consts::SHELL_EXE + " " + cmdstr );

    int result = shell->executa();
    if ( result != 0 ) {
        messagebuilder b( errors::SHELL_CMD_NOT_EXECUTED );
        b << std::to_string( result );
        throw st_error( shellCMD, b.str() );
    }

    delete shell;

    messagebuilder b( infos::EXECUTED_CMD );
    b << cmdstr;
    cout << b.str() << endl;

}
