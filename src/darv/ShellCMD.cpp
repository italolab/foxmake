
#include "ShellCMD.h"

ShellCMD::ShellCMD( Statement* parent, string cmdstr, int numberOfLinesReaded, string line ) : GenericCMD( parent, numberOfLinesReaded, line ) {
    this->cmdstr = cmdstr;
}

string ShellCMD::getCMDStr() {
    return cmdstr;
}

Statement* ShellCMD::getTask() {
    return Statement::getTask();
}