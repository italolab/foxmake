
#include "InterResult.h"

InterResult::InterResult( int numberOfLines ) {
    this->numberOfLines = numberOfLines;
    this->ok = true;
}

InterResult::InterResult( int numberOfLines, string errorMsg ) {
    this->numberOfLines = numberOfLines;
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
