
#include "PropInter.h"
#include "InterManager.h"
#include "../darv/Prop.h"

InterResult* PropInter::interprets( MainScript* parent, string line, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 0, i );
    string value = line.substr( i+1, line.length()-i );

    if ( !manager->isValidProp( name ) )
        return new InterResult( line, "Propriedade nao reconhecida: \"" + name + "\"" );

    InterResult* replaceResult = Inter::replacePropsAndVars( value, lineNumber, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    Prop* prop = new Prop( parent, name, value, lineNumber, line );
    if ( parent != nullptr )
        parent->putProperty( prop );

    return new InterResult( prop, 1, line.length() );
}
