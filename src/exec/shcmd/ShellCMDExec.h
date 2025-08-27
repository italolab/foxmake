#ifndef SHELL_CMD_EXEC_H
#define SHELL_CMD_EXEC_H

#include "../../darv/ShellCMD.h"

#include <string>

using std::string;

class ShellCMDExec {

    public:
        void exec( ShellCMD* shellCMD, void* mgr );

};

#endif
