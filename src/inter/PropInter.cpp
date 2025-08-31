
#include "PropInter.h"
#include "InterManager.h"
#include "../darv/Prop.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

InterResult* PropInter::interprets( 
            MainScript* parent, string line, int& numberOfLinesReaded, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 0, i );
    string value = line.substr( i+1, line.length()-i );

    if ( !manager->isValidProp( name ) ) {
        messagebuilder b( "Propriedade nao reconhecida: \"$1\"" );
        b << name;
        return new InterResult( line, 0, 0, b.str() );
    }

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( line, value, numberOfLinesReaded, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    Prop* prop = new Prop( parent, name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->putProperty( prop );

    numberOfLinesReaded++;

    return new InterResult( prop, numberOfLinesReaded, line.length() );
}
