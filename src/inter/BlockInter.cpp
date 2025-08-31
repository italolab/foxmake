
#include "BlockInter.h"
#include "InterManager.h"
#include "InterResult.h"
#include "it/FileIterator.h"
#include "../util/strutil.h"

#include "../error_messages.h"

#include <iostream>
using namespace std;

BlockInterResult* BlockInter::interpretsBlock( 
            Block* block, 
            BlockIterator* it, 
            int lineNumber, 
            int& numberOfLines,
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    bool ignoreFlag = false;
    bool endFound = false;
    while( !endFound && it->hasNextLine() ) {
        string line = it->nextLine();
        line = strutil::removeStartWhiteSpaces( line );

        if ( line.length() == 0 ) {
            numberOfLines++;
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
            numberOfLines++;
            continue;
        }

        int currentLineNumber = lineNumber + numberOfLines;

        InterResult* endIResult = this->interpretsEnd( block, line, currentLineNumber );
        if ( endIResult->isInterpreted() ) {
            numberOfLines++;
            endFound = true;
            continue;
        } else if ( endIResult->isErrorFound() ) {
            string error = endIResult->getErrorMsg();
            InterResult* iresult = new InterResult( line, numberOfLines, 0, error );
            return new BlockInterResult( iresult, endFound );
        }

        bool isCmd = manager->isValidCMD( line );

        InterResult* result = new InterResult( false );
        if ( isCmd )
            result = manager->interpretsCMD( block, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsVar( block, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsShellCMD( block, it, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = this->interpretsLine( block, it, line, currentLineNumber, mgr );            

        numberOfLines += result->getNumberOfLines();

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

            cout << line << "  " << numberOfLines << endl;

            InterResult* errorResult = new InterResult( resultLine, numberOfLines, 0, error );
            return new BlockInterResult( errorResult, endFound );
        }

        delete result;
    }

    InterResult* okResult = new InterResult( block, numberOfLines, 0 );
    return new BlockInterResult( okResult, endFound );
}