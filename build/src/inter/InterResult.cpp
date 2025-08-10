
#include "InterResult.h"

InterResult::InterResult( No* no, int numberOfLines ) : InterResult( no, numberOfLines, 0 ) {}

InterResult::InterResult( string errorMsg ) : InterResult( 0, 0, errorMsg ) {}

InterResult::InterResult( int numberOfLines, string erroMsg ) : InterResult( numberOfLines, 0, erroMsg ) {}

InterResult::InterResult( No* no, int numberOfLines, int numberOfColumns ) {
    this->no = no;
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->ok = true;
}

InterResult::InterResult( int numberOfLines, int numberOfColumns, string errorMsg ) {
    this->numberOfLines = numberOfLines;
    this->numberOfColumns = numberOfColumns;
    this->errorMsg = errorMsg;
    this->ok = false;
}

bool InterResult::isOk() {
    return ok;
}

int InterResult::getNumberOfLines() {
    return numberOfLines;
}

string InterResult::getErrorMsg() {
    return errorMsg;
}

No* InterResult::getNo() {
    return no;
}
