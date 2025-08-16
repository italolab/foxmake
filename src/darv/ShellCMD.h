#ifndef SHELL_CMD_H
#define SHELL_CMD_H

#include "Statement.h"
#include <string>

using std::string;

class ShellCMD : public Statement {

    private:
        string cmdstr;

    public:
        ShellCMD( Statement* parent, string cmdstr, int lineNumber, string line );

        string getCMDStr();

};

#endif

