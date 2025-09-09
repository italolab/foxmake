

#include "IFExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/Var.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

void IFExec::exec( IF* ifst, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    IFCondition* condition = ifst->getCondition();
    if ( condition == nullptr )
        throw runtime_error( errors::runtime::NULL_IF_CONDITION );

    bool conditionValue = true;
    if ( condition->getCompOperator() == "==" )
        conditionValue = ( condition->getOperand1Value() == condition->getOperand2Value() );
    else conditionValue = ( condition->getOperand1Value() != condition->getOperand2Value() );

    if ( conditionValue ) {
        manager->executeStatement( ifst->getThenStatement() );
    } else {
        manager->executeStatement( ifst->getElseStatement() );
    }   
}