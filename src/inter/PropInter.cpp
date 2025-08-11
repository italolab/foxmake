
#include "PropInter.h"
#include "../darv/Prop.h"

InterResult* PropInter::interpreta( WithPropNo* no, string line, int lineNumber, InterManager* manager ) {
    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 0, i );
    string value = line.substr( i+1, line.length()-i );

    InterResult* replaceResult = Inter::replaceProps( value, lineNumber, no );
    if ( !replaceResult->isOk() )
        return replaceResult;

    Prop* prop = new Prop( name, value );
    if ( no != nullptr )
        no->addProperty( prop );

    return new InterResult( prop, 0, line.length() );
}
