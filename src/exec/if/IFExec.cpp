

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
    InterManager* interManager = manager->getInterManager();

    int numberOfLinesReaded = ifst->getNumberOfLinesReaded();
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

    InterResult* replaceResult = interManager->replacePropsAndVarsAndDollarSigns( 
            operand1Value, numberOfLinesReaded, line, parent );    
    if ( !replaceResult->isInterpreted() )
        throw st_error( replaceResult );
    delete replaceResult;    

    replaceResult = interManager->replacePropsAndVarsAndDollarSigns( 
            operand2Value, numberOfLinesReaded, line, parent );    
    if ( !replaceResult->isInterpreted() )
        throw st_error( replaceResult );
    delete replaceResult;

    bool conditionValue = true;
    if ( compOperator == "==" )
        conditionValue = ( operand1Value == operand2Value );
    else conditionValue = ( operand1Value != operand2Value );

    if ( conditionValue ) {
        manager->executeStatement( ifst->getThenStatement() );
    } else {
        manager->executeStatement( ifst->getElseStatement() );
    }   
}