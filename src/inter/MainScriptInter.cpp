
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"
#include "../util/strutil.h"

#include "../error_messages.h"

#include <iostream>
using namespace std;

InterResult* MainScriptInter::interprets( MainScript* script, string file, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    FileIterator* it = new FileIterator( file );

    int numberOfLines = 0;
    while( it->hasNextLine() ) {
        string line = it->nextLine();
        line = strutil::removeStartWhiteSpaces( line );

        if ( line.length() == 0 ) {
            numberOfLines++;
            continue;
        }

        if ( strutil::isWhiteSpace( line[ 0 ] ) || line[ 0 ] == '#' ) {
            numberOfLines++;
            continue;
        }

        bool isCmd = manager->isValidCMD( line );

        int currentLineNumber = lineNumber + numberOfLines;

        InterResult* result = new InterResult( false );
        if ( isCmd )
            result = manager->interpretsCMD( script, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsVar( script, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound())
            result = manager->interpretsProp( script, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound())
            result = manager->interpretsTask( script, it, line, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsShellCMD( script, line, currentLineNumber );

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

            return new InterResult( resultLine, lineNumber + numberOfLines, 0, error );
        }

        delete result;
    }

    return new InterResult( script, numberOfLines, 0 );
}
