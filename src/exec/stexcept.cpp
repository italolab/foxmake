
#include "stexcept.h"

#include <sstream>

using std::stringstream;
using std::endl;

st_error::st_error( Statement* st, string msg ) : runtime_error( msg ) {
    if ( st != nullptr ) {
        this->numberOfLinesReaded = st->getNumberOfLinesReaded();
        this->line = st->getLine();
        this->isShowLine = true;
    } else {
        this->isShowLine = false;
    }
}

st_error::st_error( InterResult* result ) : runtime_error( result->getErrorMsg() ) {
    this->numberOfLinesReaded = result->getNumberOfLinesReaded();
    this->line = result->getLine();
    this->isShowLine = true;
}

void st_error::printMessage( Output& out ) const {
    if ( isShowLine ) {
        int lineNumber = numberOfLinesReaded + 1;
        out << "Erro na linha(" << std::to_string( lineNumber ) << "): ";
        out << "\"";
        out << output::red( line );
        out << "\"\n";
    }
    out << output::red( runtime_error::what() ) << "\n";
}
