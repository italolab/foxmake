#ifndef SHELL_CMD_LINE_H
#define SHELL_CMD_LINE_H

#include "GenericCMD.h"
#include <string>

using std::string;

class ShellCMDLine : public GenericCMD {

    private:
        string cmdstr;

    public:
        ShellCMDLine( Statement* parent, string cmdstr, int numberOfLinesReaded, string line );

        string getCMDStr();
        Statement* getTask();

};

#endif

