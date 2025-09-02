
#include "BlockInter.h"
#include "InterManager.h"
#include "InterResult.h"
#include "it/FileIterator.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::istringstream;

InterResult* BlockInter::interpretsBlock( 
            Block* block, 
            BlockIterator* it, 
            int& numberOfLinesReaded,
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    bool ignoreFlag = false;
    bool endFound = false;
    while( !endFound && it->hasNextLine() ) {
        string line = it->nextLine();
        line = strutil::removeStartWhiteSpaces( line );

        if ( line.length() == 0 ) {
            numberOfLinesReaded++;
            continue;
        }

        bool ignoreLineFlag = false;

        string line2 = strutil::trim( line );
        if ( line2 == "##" ) {
            ignoreFlag = !ignoreFlag;
            ignoreLineFlag = true;
        } else if ( strutil::isWhiteSpace( line[ 0 ] ) || line[ 0 ] == '#' ) {
            ignoreLineFlag = true;
        }

        if ( ignoreFlag || ignoreLineFlag ) {
            numberOfLinesReaded++;
            continue;
        }

        InterResult* endIResult = this->interpretsEnd( block, line, numberOfLinesReaded );
        if ( endIResult->isInterpreted() ) {
            numberOfLinesReaded++;
            endFound = true;
            continue;
        } else if ( endIResult->isErrorFound() ) {
            return endIResult;
        }

        bool isCmd = manager->isValidCMD( line );

        InterResult* result = new InterResult( false );
        if ( isCmd )
            result = manager->interpretsCMD( block, line, numberOfLinesReaded );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsVar( block, line, numberOfLinesReaded );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsShellCMD( block, it, line, numberOfLinesReaded );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = this->interpretsLine( block, it, line, numberOfLinesReaded, mgr );            

        if ( !result->isInterpreted() ) {
            string error;
            string resultLine;
            if ( result->isErrorFound() ) {
                error = result->getErrorMsg();
                resultLine = result->getLine();
            } else {
                error = errors::UNRECOGNIZED_LINE;
                resultLine = line;
            }

            return new InterResult( resultLine, numberOfLinesReaded, 0, error );
        }

        delete result;
    }

    if ( !endFound && this->getEndToken() != "" )
        return this->getEndTokenNotFoundInterResult();

    return new InterResult( block, numberOfLinesReaded, 0 );
}

InterResult* BlockInter::interpretsEnd( 
            Block* block, string currentLine, int& numberOfLinesReaded ) {

    string endToken = this->getEndToken();
    if ( endToken != "" ) {

        istringstream iss( currentLine );
        if ( iss.peek() == EOF )
            return new InterResult( false );

        string token;
        iss >> token;
        if ( token == endToken ) {
            if ( iss.peek() == EOF )
                return new InterResult( true );

            iss >> token;
            if ( token != "" ) {
                messagebuilder b( errors::UNNECESSARY_TOKEN );
                b << token;
                return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );        
            }
        };
    }

    return new InterResult( false );
}