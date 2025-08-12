
#include "Proc.h"

#include <sstream>

using std::stringstream;
using std::endl;

proc_error::proc_error( CMD* cmd, string msg ) : runtime_error( msg ) {
    this->cmd = cmd;
    this->lineNumber = cmd->getLineNumber();
}

proc_error::proc_error( int lineNumber, string msg ) : runtime_error( msg ) {
    this->cmd = nullptr;
    this->lineNumber = lineNumber;
}

string proc_error::message() const {
    stringstream ss;
    ss << "Erro na linha(" << lineNumber << "): ";
    if ( cmd != nullptr )
        ss << "\"" << cmd->getCMDStr() << "\"" << endl;
    ss << runtime_error::what() << endl;
    return ss.str();
}

