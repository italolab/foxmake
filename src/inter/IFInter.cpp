
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

IFInter::IFInter() {
    this->ifConditionInter = new IFConditionInter();
}

IFInter::~IFInter() {
    delete ifConditionInter;
}

InterResult* IFInter::interprets( 
            Block* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            bool isAddToParent,
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;
    
    size_t i = currentLine.find( "if" );
    size_t j = currentLine.find( "then" );

    string currLine = strutil::removeStartWhiteSpaces( currentLine );
    if ( !strutil::startsWith( currLine, "if " ) )
        return new InterResult( false );

    if ( j == string::npos )
        return new InterResult( currentLine, numberOfLinesReaded, 0, errors::IF_WITHOUT_THEN );

    if ( currentLine.length() > j+5 ) {
        string afterThenTokens = currentLine.substr( j+5, currentLine.length()-j-5 );
        afterThenTokens = strutil::trim( afterThenTokens );
        
        if ( afterThenTokens != "" ) {
            messagebuilder b( errors::UNNECESSARY_TOKEN );
            b << afterThenTokens;
            return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );
        }
    }

    string condition = currentLine.substr( i+3, j-i-3 );
    string value1;
    string value2;
    string compOperator;

    InterResult* result = ifConditionInter->interprets( 
            parent, condition, value1, value2, compOperator, currentLine, numberOfLinesReaded, mgr );

    if ( result->isErrorFound() )
        return result;    

    IF* ifst = new IF( parent, numberOfLinesReaded, currentLine );
    ifst->setCondition( new IFCondition( value1, value2, compOperator ) );
    
    Statement* thenSt = nullptr;
    Statement* elseSt = nullptr;

    stringstream ss;

    int startNumberOfLinesReaded = numberOfLinesReaded;

    numberOfLinesReaded++;
    string line;
    int ifCount = 1;
    while( ifCount > 0 && it->hasNextLine() ) {
        string line = it->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        if ( strutil::startsWith( line2, "if" ) ) {
            ss << line << "\n";
            ifCount++;
        } else if ( strutil::startsWith( line2, "else" ) ) {
            if ( ifCount == 1 ) {
                if ( thenSt != nullptr )
                    return new InterResult( currentLine, numberOfLinesReaded, 0, errors::IF_UNNECESSARY_ELSE );

                thenSt = new Block( parent, numberOfLinesReaded, currentLine );

                StringIterator* it2 = new StringIterator( ss.str() );

                ss.str("");

                InterResult* result = manager->interpretsBlock( (Block*)thenSt, it2, numberOfLinesReaded );
                if ( result->isErrorFound() )
                    return result;

                if ( strutil::startsWith( line2, "else if" ) ) {                        
                    string line3 = line2.substr( 5, line2.length()-5 );

                    InterResult* result = this->interprets( parent, it, line3, numberOfLinesReaded, false, mgr );
                    if ( result->isErrorFound() )
                        return result;

                    elseSt = result->getStatement();

                    ifCount--;
                } else {
                    numberOfLinesReaded++;                
                }
            } else if ( ifCount > 1 ) {
                ss << line << "\n";
            }
        } else if ( strutil::startsWith( line2, "endif" ) ) {
            ifCount--;
            if ( ifCount != 0 )
                ss << line << "\n";
        } else {
            ss << line << "\n";
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
    
    if ( parent != nullptr && isAddToParent )
        parent->addStatement( ifst );

    return new InterResult( ifst, numberOfLinesReaded, 0 );
}
