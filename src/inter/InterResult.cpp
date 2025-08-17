
#include "InterResult.h"

InterResult::InterResult( Statement* statement, int numberOfLines, int numberOfColumns ) {
    this->statement = statement;
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->line = "";
    this->errorMsg = "";
    this->interpreted = true;
    this->errorFound = false;
}

InterResult::InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg ) {
    this->statement = nullptr;
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->line = line;
    this->errorMsg = errorMsg;
    this->interpreted = false;
    this->errorFound = true;
}

InterResult::InterResult( bool interpreted ) {
    this->statement = nullptr;
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
    return statement;
}
