

#include "VarAttrExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/Var.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

void VarAttrExec::exec( VarAttr* varAttr, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();

    string varName = varAttr->getName();
    string varValue = varAttr->getValue();
    int numberOfLinesReaded = varAttr->getNumberOfLinesReaded();
    string line = varAttr->getLine();
    Block* parent = (Block*)varAttr->getParent();

    if ( parent == nullptr )
        throw runtime_error( errors::runtime::NULL_BLOCK_STATEMENT );

    bool isErrorIfNotFound = true;
    InterResult* result = interManager->replacePropsAndVarsAndDollarSigns( 
            varValue, numberOfLinesReaded, line, isErrorIfNotFound, parent );

    if ( result->isErrorFound() )
        throw st_error( result );

    Var* var = new Var( varName, varValue, numberOfLinesReaded, line );
    parent->putLocalVar( var );    
}