
#include "Proc.h"

#include <sstream>

using std::stringstream;
using std::endl;

proc_error::proc_error( CMD* cmd, string msg ) : runtime_error( msg ) {
    this->lineNumber = cmd->getLineNumber();
    this->line = cmd->getCMDStr();
}

proc_error::proc_error( InterResult* result ) : runtime_error( result->getErrorMsg() ) {
    this->lineNumber = result->getNumberOfLines();
    this->line = result->getLine();
}

string proc_error::message() const {
    stringstream ss;
    ss << "Erro na linha(" << lineNumber << "): ";
    ss << "\"" << line << "\"" << endl;
    ss << runtime_error::what() << endl;
    return ss.str();
}

