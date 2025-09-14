
#include "NoInBlockVarAttrInter.h"
#include "InterManager.h"
#include "../darv/Var.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

InterResult* NoInBlockVarAttrInter::interprets( 
            Block* parent, string line, int& numberOfLinesReaded, void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '$' )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 1, i-1 );
    string value = line.substr( i+1, line.length()-i );

    if ( manager->isPredefinedVar( parent, name ) ) {
        messagebuilder b( errors::TRY_CHANGE_PREDEFINED_VAR );
        b << name;
        return new InterResult( line, numberOfLinesReaded, 0, b.str() );
    }

    InterResult* replaceResult = manager->replacePropsAndVarsAndDollarSigns(
            value, numberOfLinesReaded, line, parent );

    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    Var* var = new Var( name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->putLocalVar( var );

    numberOfLinesReaded++;

    return new InterResult( nullptr, numberOfLinesReaded, line.length() );
}
