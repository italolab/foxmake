
#include "Statement.h"
#include <typeinfo>

Statement::Statement( Statement* parent, int lineNumber ) {
    this->parent = parent;
    this->lineNumber = lineNumber;
}

Statement* Statement::getParent() {
    return parent;
}

int Statement::getLineNumber() {
    return lineNumber;
}
