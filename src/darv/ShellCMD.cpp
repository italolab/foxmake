
#include "ShellCMD.h"

ShellCMD::ShellCMD( Statement* parent, string cmdstr, int lineNumber, string line ) : GenericCMD( parent, lineNumber, line ) {
    this->cmdstr = cmdstr;
}

string ShellCMD::getCMDStr() {
    return cmdstr;
}

Statement* ShellCMD::getTask() {
    return Statement::getTask();
}