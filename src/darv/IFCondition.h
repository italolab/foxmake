#ifndef IF_CONDITION_H
#define IF_CONDITION_H

#include <string>

using std::string;

class IFCondition {

    private:
        string operand1Value;
        string operand2Value;
        string compOperator;

        bool operand1ValuePropOrVar;
        bool operand2ValuePropOrVar;

    public:
        IFCondition( string operand1Value, 
            string operand2Value, 
            string compOperator, 
            bool operand1PropOrVar,
            bool operand2PropOrVar );

        string getOperand1Value();
        string getOperand2Value();
        string getCompOperator();

        bool isOperand1ValuePropOrVar();
        bool isOperand2ValuePropOrVar();

};

#endif