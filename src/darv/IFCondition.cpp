
#include "IFCondition.h"

IFCondition::IFCondition( string operand1Value, string operand2Value, string compOperator ) {
    this->operand1Value = operand1Value;
    this->operand2Value = operand2Value;
    this->compOperator = compOperator;
}

string IFCondition::getOperand1Value() {
    return operand1Value;
}

string IFCondition::getOperand2Value() {
    return operand2Value;
}

string IFCondition::getCompOperator() {
    return compOperator;
}