

#include "IFExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/Var.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

#include <iostream>
using namespace std;

void IFExec::exec( IF* ifst, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();

    string line = ifst->getLine();
    Block* parent = (Block*)ifst->getParent();

    if ( parent == nullptr )
        throw runtime_error( errors::runtime::NULL_PARENT );

    IFCondition* condition = ifst->getCondition();
    if ( condition == nullptr )
        throw runtime_error( errors::runtime::NULL_IF_CONDITION );

    string operand1Value = condition->getOperand1Value();
    string operand2Value = condition->getOperand2Value();
    string compOperator = condition->getCompOperator();

    if ( condition->isOperand1ValuePropOrVar() ) {
        if ( !interManager->isPropOrVar( parent, operand1Value ) ) {
            messagebuilder b( errors::PROP_OR_VAR_NOT_FOUND );
            b << operand1Value;
            throw st_error( ifst, b.str() );
        }
        operand1Value = interManager->getPropOrVarValue( parent, operand1Value );            
    }

    if ( condition->isOperand2ValuePropOrVar() ) {
        if ( !interManager->isPropOrVar( parent, operand2Value ) ) {
            messagebuilder b( errors::PROP_OR_VAR_NOT_FOUND );
            b << operand2Value;
            throw st_error( ifst, b.str() );
        }
        operand2Value = interManager->getPropOrVarValue( parent, operand2Value );
    }

    bool conditionValue = true;
    if ( compOperator == "==" )
        conditionValue = ( operand1Value == operand2Value );
    else conditionValue = ( operand1Value != operand2Value );

    if ( conditionValue ) {
        if ( ifst->getThenStatement() != nullptr )
            manager->executeStatement( ifst->getThenStatement() );
    } else {
        if ( ifst->getElseStatement() != nullptr )
            manager->executeStatement( ifst->getElseStatement() );
    }   
}