
#include "Proc.h"

#include <sstream>

using std::stringstream;
using std::endl;

proc_error::proc_error( CMD* cmd, string msg ) : runtime_error( msg ) {
    this->cmd = cmd;
}

string proc_error::message() const {
    stringstream ss;
    ss << "Erro na linha(" << cmd->getLineNumber() << "): \"" << cmd->getCMDStr() << "\"" << endl;
    ss << runtime_error::what() << endl;
    return ss.str();
}

Proc::Proc( string cmdName ) {
    this->cmdName = cmdName;
}

string Proc::getCMDName() {
    return cmdName;
}

