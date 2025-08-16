#ifndef SHELL_CMD_INTER_H
#define SHELL_CMD_INTER_H

#include "Inter.h"

#include <string>

using std::string;

class ShellCMDInter : public Inter {

    public:
        InterResult* interprets( Block* parent, string line, int lineNumber, void* mgr );

};

#endif

