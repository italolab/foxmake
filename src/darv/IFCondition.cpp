
#include "IFCondition.h"

IFCondition::IFCondition( string operand1Value, 
                    string operand2Value, 
                    string compOperator,
                    bool operand1ValuePropOrVar,
                    bool operand2ValuePropOrVar ) {

    this->operand1Value = operand1Value;
    this->operand2Value = operand2Value;
    this->compOperator = compOperator;
    this->operand1ValuePropOrVar = operand1ValuePropOrVar;
    this->operand2ValuePropOrVar = operand2ValuePropOrVar;
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

bool IFCondition::isOperand1ValuePropOrVar() {
    return operand1ValuePropOrVar;
}

bool IFCondition::isOperand2ValuePropOrVar() {
    return operand2ValuePropOrVar;
}