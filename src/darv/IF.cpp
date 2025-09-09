
#include "IF.h"

IF::IF( Statement* parent, int numberOfLinesReaded, string line ) : Statement( parent, numberOfLinesReaded, line ) {
    this->condition = nullptr;
    this->thenStatement = nullptr;
    this->elseStatement = nullptr;
}

IF::~IF() {
    if ( thenStatement != nullptr )
        delete thenStatement;
    if ( elseStatement != nullptr )
        delete elseStatement;
}

IFCondition* IF::getCondition() {
    return condition;
}

Statement* IF::getThenStatement() {
    return thenStatement;
}

Statement* IF::getElseStatement() {
    return elseStatement;
}

void IF::setCondition( IFCondition* condition ) {
    this->condition = condition;
}

void IF::setThenStatement( Statement* block ) {
    this->thenStatement = block;
}

void IF::setElseStatement( Statement* block ) {
    this->elseStatement = block;
}