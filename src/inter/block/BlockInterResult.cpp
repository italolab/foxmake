
#include "BlockInterResult.h"

BlockInterResult::BlockInterResult( InterResult* result, bool endFound ) {
    this->interResult = result;
    this->endFound = endFound;
}

InterResult* BlockInterResult::getInterResult() {
    return interResult;
}

bool BlockInterResult::isEndFound() {
    return endFound;
}