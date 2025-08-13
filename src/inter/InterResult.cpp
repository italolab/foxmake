
#include "InterResult.h"

InterResult::InterResult( Statement* no, int numberOfLines ) : InterResult( no, numberOfLines, 0 ) {}

InterResult::InterResult( string line, string errorMsg ) : InterResult( line, 0, 0, errorMsg ) {}

InterResult::InterResult( string line, int numberOfLines, string erroMsg ) : InterResult( line, numberOfLines, 0, erroMsg ) {}

InterResult::InterResult( Statement* no, int numberOfLines, int numberOfColumns ) {
    this->no = no;
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->line = "";
    this->errorMsg = "";
    this->interpreted = true;
    this->errorFound = false;
}

InterResult::InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg ) {
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->line = line;
    this->errorMsg = errorMsg;
    this->interpreted = false;
    this->errorFound = true;
}

InterResult::InterResult( bool interpreted ) {
    this->numberOfLines = ( interpreted ? 1 : 0 );
    this->numberOfColumns = 0;
    this->line = "";
    this->errorMsg = "";
    this->interpreted = interpreted;
    this->errorFound = false;
}

bool InterResult::isInterpreted() {
    return interpreted;
}

bool InterResult::isErrorFound() {
    return errorFound;
}

int InterResult::getNumberOfLines() {
    return numberOfLines;
}

string InterResult::getLine() {
    return line;
}

string InterResult::getErrorMsg() {
    return errorMsg;
}

Statement* InterResult::getStatement() {
    return no;
}
