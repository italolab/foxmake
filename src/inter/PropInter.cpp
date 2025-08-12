
#include "PropInter.h"
#include "../darv/Prop.h"

InterResult* PropInter::interprets( MainScript* parent, string line, int lineNumber, InterManager* manager ) {
    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 0, i );
    string value = line.substr( i+1, line.length()-i );

    InterResult* replaceResult = Inter::replacePropsAndVars( value, lineNumber, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    Prop* prop = new Prop( name, value );
    if ( parent != nullptr )
        parent->putProperty( prop );

    return new InterResult( prop, 1, line.length() );
}
