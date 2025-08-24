#ifndef SHELL_CMD_H
#define SHELL_CMD_H

#include "GenericCMD.h"
#include <string>

using std::string;

class ShellCMD : public GenericCMD {

    private:
        string cmdstr;

    public:
        ShellCMD( Statement* parent, string cmdstr, int lineNumber, string line );

        string getCMDStr();
        Statement* getTask();

};

#endif

