
#include "ShellCMDLine.h"

ShellCMDLine::ShellCMDLine( Statement* parent, string cmdstr, int numberOfLinesReaded, string line ) : GenericCMD( parent, numberOfLinesReaded, line ) {
    this->cmdstr = cmdstr;
}

string ShellCMDLine::getCMDStr() {
    return cmdstr;
}

Statement* ShellCMDLine::getTask() {
    return Statement::getTask();
}