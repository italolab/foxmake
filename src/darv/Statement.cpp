
#include "Statement.h"

Statement::Statement( Statement* parent, int lineNumber, string line ) {
    this->parent = parent;
    this->lineNumber = lineNumber;
    this->line = line;
}

Statement::~Statement() {}

Statement* Statement::getParent() {
    return parent;
}

int Statement::getLineNumber() {
    return lineNumber;
}

string Statement::getLine() {
    return line;
}
