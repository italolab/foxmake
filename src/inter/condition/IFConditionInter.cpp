
#include "IFConditionInter.h"
#include "../InterManager.h"
#include "../../darv/MainScript.h"
#include "../../darv/Block.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <stdexcept>

using std::runtime_error;

InterResult* IFConditionInter::interprets( 
            Block* parent,
            string condition,
            string& value1, 
            string& value2, 
            string& compOperator,
            string line, 
            int numberOfLinesReaded,
            void* mgr ) {
        
    InterManager* manager = (InterManager*)mgr;

    condition = strutil::removeStartWhiteSpaces( condition );
    condition = strutil::removeEndWhiteSpaces( condition );

    size_t k = condition.find( "==" );
    if ( k != string::npos ) {
        compOperator = "==";
    } else {
        k = condition.find( "!=" );
        if ( k != string::npos )
            compOperator = "!=";
    }
    
    if ( k == string::npos )
        return new InterResult( line, numberOfLinesReaded, 0, errors::IF_CONDITION_WITHOUT_COMP_OPERATOR );

    string operand1 = condition.substr( 0, k );
    string operand2 = condition.substr( k+2, condition.length()-k-2 );

    operand1 = strutil::removeStartWhiteSpaces( operand1 );
    operand1 = strutil::removeEndWhiteSpaces( operand1 );

    operand2 = strutil::removeStartWhiteSpaces( operand2 );
    operand2 = strutil::removeEndWhiteSpaces( operand2 );

    if ( strutil::startsWith( operand1, "\"" ) ) {
        if ( !strutil::endsWith( operand1, "\"" ) )
            return new InterResult( line, numberOfLinesReaded, 0, errors::IF_OPERAND1_WITHOUT_CLOSE_QUOTES );

        value1 = operand1.substr( 1, operand1.length()-2 );
    } else {
        if ( manager->isPropOrVar( parent, operand1 ) ) {
            value1 = operand1;
        } else {
            messagebuilder b( errors::PROP_OR_VAR_NOT_FOUND );
            b << operand1;
            return new InterResult( line, numberOfLinesReaded, 0, b.str() );
        }
    }

    if ( strutil::startsWith( operand2, "\"" ) ) {
        if ( !strutil::endsWith( operand2, "\"" ) )
            return new InterResult( line, numberOfLinesReaded, 0, errors::IF_OPERAND2_WITHOUT_CLOSE_QUOTES );
         
        value2 = operand2.substr( 1, operand2.length()-2 );
    } else {
        if ( manager->isPropOrVar( parent, operand2 ) ) {
            value2 = operand2;
        } else {
            messagebuilder b( errors::PROP_OR_VAR_NOT_FOUND );
            b << operand2;
            return new InterResult( line, numberOfLinesReaded, 0, b.str() );
        }
    }

    return new InterResult( true );
}