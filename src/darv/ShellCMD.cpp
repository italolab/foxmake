
#include "ShellCMD.h"

ShellCMD::ShellCMD( Statement* parent, string cmdstr, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
    this->cmdstr = cmdstr;
}

string ShellCMD::getCMDStr() {
    return cmdstr;
}
