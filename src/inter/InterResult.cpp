
#include "InterResult.h"

InterResult::InterResult( Statement* statement, int numberOfLines, int numberOfColumns ) {
    this->statement = statement;
    this->numberOfLinesReaded = numberOfLines;
    this->numberOfColumnsReaded = numberOfColumns;
    this->line = "";
    this->errorMsg = "";
    this->interpreted = true;
    this->errorFound = false;
}

InterResult::InterResult( string line, int numberOfLines, int numberOfColumns, string errorMsg ) {
    this->statement = nullptr;
    this->numberOfLinesReaded = numberOfLines;
    this->numberOfColumnsReaded = numberOfColumns;
    this->line = line;
    this->errorMsg = errorMsg;
    this->interpreted = false;
    this->errorFound = true;
}

InterResult::InterResult( bool interpreted ) {
    this->statement = nullptr;
    this->numberOfLinesReaded = ( interpreted ? 1 : 0 );
    this->numberOfColumnsReaded = 0;
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

int InterResult::getNumberOfLinesReaded() {
    return numberOfLinesReaded;
}

int InterResult::getNumberOfColumnsReaded() {
    return numberOfColumnsReaded;
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
