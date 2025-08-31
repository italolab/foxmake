
#include "BlockInter.h"
#include "InterManager.h"
#include "InterResult.h"
#include "it/FileIterator.h"
#include "../util/strutil.h"

#include "../error_messages.h"

BlockInterResult* BlockInter::interpretsBlock( 
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
            string error = endIResult->getErrorMsg();
            InterResult* iresult = new InterResult( line, numberOfLinesReaded, 0, error );
            return new BlockInterResult( iresult, endFound );
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

            InterResult* errorResult = new InterResult( resultLine, numberOfLinesReaded, 0, error );
            return new BlockInterResult( errorResult, endFound );
        }

        delete result;
    }

    InterResult* okResult = new InterResult( block, numberOfLinesReaded, 0 );
    return new BlockInterResult( okResult, endFound );
}