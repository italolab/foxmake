
#include "VarInter.h"
#include "../darv/Var.h"

InterResult* VarInter::interprets( Block* block, string line, int lineNumber, InterManager* manager ) {
    if ( line.length() == 0 )
        return new InterResult( false );
    if ( line[ 0 ] != '$' )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 1, i );
    string value = line.substr( i+1, line.length()-i );

    InterResult* replaceResult = Inter::replaceProps( value, lineNumber, block );
    if ( !replaceResult->isOk() )
        return replaceResult;

    Var* var = new Var( block, name, value );
    if ( block != nullptr )
        block->addLocalVar( var );

    return new InterResult( var, 0, line.length() );
}
