#ifndef IF_CONDITION_H
#define IF_CONDITION_H

#include <string>

using std::string;

class IFCondition {

    private:
        string operand1Value;
        string operand2Value;
        string compOperator;

    public:
        IFCondition( string operand1Value, string operand2Value, string compOperator );

        string getOperand1Value();
        string getOperand2Value();
        string getCompOperator();

};

#endif