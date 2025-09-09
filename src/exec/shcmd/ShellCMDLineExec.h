#ifndef SHELL_CMD_LINE_EXEC_H
#define SHELL_CMD_LINE_EXEC_H

#include "../../darv/ShellCMDLine.h"

#include <string>

using std::string;

class ShellCMDLineExec {

    public:
        void exec( ShellCMDLine* shellCMD, void* mgr );

};

#endif
