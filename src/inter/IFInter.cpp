
#include "IFInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "../darv/IF.h"
#include "../darv/MainScript.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;

InterResult* IFInter::interprets( 
            Block* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;
    
    size_t i = currentLine.find( "if" );
    size_t j = currentLine.find( "then" );

    if ( i == string::npos )
        return new InterResult( false );

    if ( j == string::npos )
        return new InterResult( currentLine, numberOfLinesReaded, 0, errors::IF_WITHOUT_THEN );

    string afterThenTokens = currentLine.substr( j+5, currentLine.length()-j-5 );
    afterThenTokens = strutil::trim( afterThenTokens );
    
    if ( afterThenTokens != "" ) {
        messagebuilder b( errors::UNNECESSARY_TOKEN );
        b << afterThenTokens;
        return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );
    }

    string condition = currentLine.substr( i+3, j-i-3 );
    string value1;
    string value2;
    string compOperator;

    InterResult* result = this->interpretsCondition( 
            parent, condition, value1, value2, compOperator, currentLine, numberOfLinesReaded );

    if ( result->isErrorFound() )
        return result;    

    IF* ifst = new IF( parent, numberOfLinesReaded, currentLine );
    if ( compOperator == "==" )
        ifst->setConditionValue( value1 == value2 );
    else ifst->setConditionValue( value1 != value2 );

    Statement* thenSt = nullptr;
    Statement* elseSt = nullptr;

    stringstream ss;

    int startNumberOfLinesReaded = numberOfLinesReaded;

    numberOfLinesReaded++;
    string line;
    bool elseFound = false;
    int ifCount = 1;
    while( ifCount > 0 && it->hasNextLine() ) {
        string line = it->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        if ( strutil::startsWith( line2, "if" ) ) {
            ifCount++;
        } else if ( strutil::startsWith( line2, "else" ) ) {
            if ( ifCount == 1 ) {
                if ( thenSt != nullptr )
                    return new InterResult( currentLine, numberOfLinesReaded, 0, errors::IF_UNNECESSARY_ELSE );

                thenSt = new Block( parent, numberOfLinesReaded, currentLine );

                StringIterator* it = new StringIterator( ss.str() );

                ss.str("");

                InterResult* result = manager->interpretsBlock( (Block*)thenSt, it, numberOfLinesReaded );
                if ( result->isErrorFound() )
                    return result;

                if ( strutil::startsWith( line2, "else if" ) ) {                        
                    string line3 = line2.substr( 5, line2.length()-5 );

                    InterResult* result = this->interprets( nullptr, it, line3, numberOfLinesReaded, mgr );
                    if ( result->isErrorFound() )
                        return result;

                    elseSt = result->getStatement();

                    ifCount--;
                } else {
                    numberOfLinesReaded++;                
                }

            }
        } else if ( strutil::startsWith( line2, "endif" ) ) {
            ifCount--;
        } else {
            ss << line;
        }
    }

    if ( ifCount > 0 )
        return new InterResult( currentLine, startNumberOfLinesReaded, 0, errors::ENDIF_NOT_FOUND );


    Block* thenOrElseBlock = nullptr;
    if ( thenSt == nullptr ) {
        thenSt = new Block( parent, numberOfLinesReaded, currentLine );
        thenOrElseBlock = (Block*)thenSt;
    } else if ( elseSt == nullptr ) {
        elseSt = new Block( parent, numberOfLinesReaded, currentLine );
        thenOrElseBlock = (Block*)elseSt;
    }

    if ( thenOrElseBlock != nullptr ) {
        StringIterator* it = new StringIterator( ss.str() );
        InterResult* result = manager->interpretsBlock( thenOrElseBlock, it, numberOfLinesReaded );
        if ( result->isErrorFound() )
            return result;
        

        numberOfLinesReaded++;
    }

    ifst->setThenStatement( thenSt );
    ifst->setElseStatement( elseSt );
    
    if ( parent != nullptr )
        parent->addStatement( ifst );

    return new InterResult( ifst, numberOfLinesReaded, 0 );
}

InterResult* IFInter::interpretsCondition( 
            Block* parent,
            string condition,
            string& value1, 
            string& value2, 
            string& compOperator,
            string line, 
            int numberOfLinesReaded ) {

    condition = strutil::removeStartWhiteSpaces( condition );
    condition = strutil::removeEndWhiteSpaces( condition );

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( line, condition, numberOfLinesReaded, parent );
    if ( replaceResult->isErrorFound() )
        return replaceResult;

    string compOperator = "";

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
    operand2 = strutil::removeEndWhiteSpaces( operand1 );

    string value1 = "";
    if ( strutil::startsWith( operand1, "\"" ) ) {
        if ( !strutil::endsWith( operand1, "\"" ) )
            return new InterResult( line, numberOfLinesReaded, 0, errors::IF_OPERAND1_WITHOUT_CLOSE_QUOTES );

        value1 = operand1.substr( 1, operand1.length()-2 );
    } else {
        string errorMsg = "";
        bool varOrPropFound = this->loadVarOrPropertyValueOfOperand( parent, operand1, value1, errorMsg );
        if ( !varOrPropFound )
            return new InterResult( line, numberOfLinesReaded, 0, errorMsg );
    }

    string value2 = "";
    if ( strutil::startsWith( operand2, "\"" ) ) {
        if ( !strutil::endsWith( operand2, "\"" ) )
            return new InterResult( line, numberOfLinesReaded, 0, errors::IF_OPERAND2_WITHOUT_CLOSE_QUOTES );
         
        value2 = operand2.substr( 1, operand2.length()-2 );
    } else {
        string errorMsg = "";
        bool varOrPropFound = this->loadVarOrPropertyValueOfOperand( parent, operand2, value2, errorMsg );
        if ( !varOrPropFound )
            return new InterResult( line, numberOfLinesReaded, 0, errorMsg );
    }

    return new InterResult( true );
}

bool IFInter::loadVarOrPropertyValueOfOperand( 
            Block* parent, 
            string operand, 
            string& value, 
            string& errorMsg ) {

    Var* var = parent->getVar( operand );
    if ( var == nullptr ) {
        Statement* root = parent->getRoot();
        if ( root == nullptr )
            throw runtime_error( errors::runtime::NULL_ROOT_STATEMENT );

        MainScript* script = (MainScript*)root;
        Prop* prop = script->getProperty( operand );
        if ( prop == nullptr ) {
            messagebuilder b( errors::VARIABLE_OR_PROPERTY_NOT_FOUND );
            b << operand;
            errorMsg = b.str();
            return false;
        }

        value = prop->getValue();
        return true;
    }

    value = var->getValue();
    return true;
}