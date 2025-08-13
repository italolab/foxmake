
#include "VarInter.h"
#include "InterManager.h"
#include "../darv/Var.h"

InterResult* VarInter::interprets( Block* parent, string line, int lineNumber, void* mgr ) {
    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '$' )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 1, i-1 );
    string value = line.substr( i+1, line.length()-i );

    InterResult* replaceResult = Inter::replacePropsAndVars( value, lineNumber, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    Var* var = new Var( parent, name, value, lineNumber, line );
    if ( parent != nullptr )
        parent->putLocalVar( var );

    return new InterResult( var, 1, line.length() );
}
