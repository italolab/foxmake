
#include "stexcept.h"

#include <sstream>

using std::stringstream;
using std::endl;

st_error::st_error( Statement* st, string msg ) : runtime_error( msg ) {
    if ( st != nullptr ) {
        this->lineNumber = st->getLineNumber();
        this->line = st->getLine();
        this->isShowLine = true;
    } else {
        this->isShowLine = false;
    }
}

st_error::st_error( InterResult* result ) : runtime_error( result->getErrorMsg() ) {
    this->lineNumber = result->getNumberOfLines();
    this->line = result->getLine();
    this->isShowLine = true;
}

void st_error::printMessage( Output& out ) const {
    if ( isShowLine ) {
        out << "Erro na linha(" << std::to_string( lineNumber ) << "): ";
        out << "\"";
        out << output::red( line );
        out << "\"\n";
    }
    out << output::red( runtime_error::what() ) << "\n";
}
