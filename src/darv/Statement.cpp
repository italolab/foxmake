
#include "Statement.h"
#include "Block.h"
#include "Task.h"

Statement::Statement( Statement* parent, int lineNumber, string line ) {
    this->parent = parent;
    this->numberOfLinesReaded = lineNumber;
    this->line = line;
}

Statement::~Statement() {}

Statement* Statement::getRoot() {
    if ( dynamic_cast<Block*>( this ) && parent == nullptr )
        return this;

    if ( Statement::getParent() == nullptr )
        return nullptr;
    return ((Block*)parent)->getRoot();
}

Statement* Statement::getTask() {
    if ( dynamic_cast<Task*>( this ) )
        return this;

    if ( Statement::getParent() == nullptr )
        return nullptr;
    return ((Block*)parent)->getTask();
}

Statement* Statement::getParent() {
    return parent;
}

int Statement::getNumberOfLinesReaded() {
    return numberOfLinesReaded;
}

string Statement::getLine() {
    return line;
}
