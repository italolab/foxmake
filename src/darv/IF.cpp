
#include "IF.h"

IF::IF( Statement* parent, int numberOfLinesReaded, string line ) : Statement( parent, numberOfLinesReaded, line ) {
    this->thenStatement = nullptr;
    this->elseStatement = nullptr;
    this->conditionValue = true;
}

IF::~IF() {
    if ( thenStatement != nullptr )
        delete thenStatement;
    if ( elseStatement != nullptr )
        delete elseStatement;
}

bool IF::getConditionValue() {
    return conditionValue;
}

Statement* IF::getThenStatement() {
    return thenStatement;
}

Statement* IF::getElseStatement() {
    return elseStatement;
}

void IF::setConditionValue( bool value ) {
    this->conditionValue = value;
}

void IF::setThenStatement( Statement* block ) {
    this->thenStatement = block;
}

void IF::setElseStatement( Statement* block ) {
    this->elseStatement = block;
}