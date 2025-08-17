
#include "stexcept.h"

#include <sstream>

using std::stringstream;
using std::endl;

st_error::st_error( Statement* st, string msg ) : runtime_error( msg ) {
    this->st = st;
}

st_error::st_error( InterResult* result ) : runtime_error( result->getErrorMsg() ) {
    this->st = result->getStatement();
}

string st_error::message() const {
    stringstream ss;
    if ( st != nullptr ) {
        ss << "Erro na linha(" << st->getLineNumber() << "): ";
        ss << "\"" << st->getLine() << "\"" << endl;
    }
    ss << runtime_error::what();
    return ss.str();
}
