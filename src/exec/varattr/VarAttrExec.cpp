

#include "VarAttrExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../darv/Var.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <iostream>
using namespace std;

void VarAttrExec::exec( VarAttr* varAttr, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    InterManager* interManager = manager->getInterManager();

    string varName = varAttr->getName();
    string varValue = varAttr->getValue();
    int numberOfLinesReaded = varAttr->getNumberOfLinesReaded();
    string line = varAttr->getLine();
    Block* parent = (Block*)varAttr->getParent();

    if ( parent == nullptr )
        throw runtime_error( errors::runtime::NULL_PARENT );

    InterResult* result = interManager->replacePropsAndVarsAndDollarSigns( 
            varValue, numberOfLinesReaded, line, parent );
    if ( result->isErrorFound() )
        throw st_error( result );
    delete result;

    Var* existentVar = ((MainScript*)parent->getRoot())->getPredefinedVar( varName );
    if ( existentVar != nullptr ) {
        messagebuilder b( errors::VAR_ATTR_TO_PREDEFINED_VAR );
        b << varName;
        throw st_error( varAttr, b.str() );
    }

    existentVar = parent->getVar( varName );
    if ( existentVar != nullptr ) {
        existentVar->setValue( varValue );
    } else {
        Var* var = new Var( varName, varValue, numberOfLinesReaded, line );
        parent->putLocalVar( var );    
    }
}