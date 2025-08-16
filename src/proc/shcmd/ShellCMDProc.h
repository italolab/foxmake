#ifndef SHELL_CMD_PROC_H
#define SHELL_CMD_PROC_H

#include "../../darv/ShellCMD.h"

#include <string>

using std::string;

class ShellCMDProc {

    public:
        void proc( ShellCMD* shellCMD, void* mgr );

};

#endif
