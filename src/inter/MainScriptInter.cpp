
#include "MainScriptInter.h"
#include "InterManager.h"
#include "it/FileIterator.h"
#include "../darv/MainScript.h"
#include "../util/strutil.h"

MainScriptInter::MainScriptInter( BlockInterDriver* drv ) {
    this->drv = drv;
}

InterResult* MainScriptInter::interprets( MainScript* script, string file, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    vector<string> validCMDs = drv->validCMDNames();

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

        bool isCmd = manager->isValidCMD( line, validCMDs );

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

        numberOfLines += result->getNumberOfLines();

        if ( !result->isInterpreted() ) {
            string error;
            if ( result->isErrorFound() )
                error = result->getErrorMsg();
            else error = "Linha nao reconhecida como instrucao valida.";

            return new InterResult( result->getLine(), numberOfLines, error );
        }
    }

    return new InterResult( script, numberOfLines );
}
