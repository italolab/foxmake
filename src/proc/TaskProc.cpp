
#include "TaskProc.h"

#include <sstream>

using std::stringstream;
using std::endl;

taskproc_error::taskproc_error( string msg ) : taskproc_error( nullptr, msg ) {}

taskproc_error::taskproc_error( Statement* st, string msg ) : runtime_error( msg ) {
    this->st = st;
}

string taskproc_error::message() const {
    stringstream ss;
    if ( st != nullptr ) {
        ss << "Erro na linha(" << st->getLineNumber() << "): ";
        ss << "\"" << st->getLine() << "\"" << endl;
    }
    ss << runtime_error::what() << endl;
    return ss.str();
}


