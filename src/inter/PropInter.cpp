
#include "PropInter.h"
#include "../darv/Prop.h"

InterResult* PropInter::interpreta( WithPropNo* no, string str, int lineNumber, InterManager* manager ) {
    size_t i = str.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = str.substr( 0, i );
    string value = str.substr( i+1, str.length()-i );

    InterResult* replaceResult = Inter::replaceProps( value, lineNumber, no );
    if ( !replaceResult->isOk() )
        return replaceResult;

    delete replaceResult;

    Prop* prop = new Prop( name, value );
    return new InterResult( prop, 0, str.length() );
}
