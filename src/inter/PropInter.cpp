
#include "PropInter.h"
#include "InterManager.h"
#include "../darv/Prop.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

InterResult* PropInter::interprets( 
            MainScript* parent, string line, int& numberOfLinesReaded, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    string line2 = strutil::removeStartWhiteSpaces( line );
    if ( strutil::startsWith( line2, "$" ) )
        return new InterResult( false );

    size_t i = line.find( '=' );
    if ( i == string::npos )
        return new InterResult( false );

    string name = line.substr( 0, i );
    string value = line.substr( i+1, line.length()-i );

    if ( !manager->isValidProp( name ) ) {
        messagebuilder b( errors::PROPERTY_NOT_FOUND );
        b << name;
        return new InterResult( line, numberOfLinesReaded, 0, b.str() );
    }

    bool isErrorIfNotFound = true;
    InterResult* replaceResult = manager->replacePropsAndVarsAndDollarSigns( 
            value, numberOfLinesReaded, line, isErrorIfNotFound, parent );
            
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

    delete replaceResult;

    Prop* prop = new Prop( name, value, numberOfLinesReaded, line );
    if ( parent != nullptr )
        parent->putProperty( prop );

    numberOfLinesReaded++;

    return new InterResult( nullptr, numberOfLinesReaded, line.length() );
}
