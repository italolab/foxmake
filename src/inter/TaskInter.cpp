
#include "TaskInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "../darv/Task.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

TaskInter::TaskInter( BlockInterDriver* drv ) {
    this->drv = drv;
}

InterResult* TaskInter::interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    istringstream iis( currentLine );

    if ( iis.peek() == EOF )
        return new InterResult( false );

    string taskName;
    iis >> taskName;

    if( iis.peek() == EOF )
        return new InterResult( false );

    string openBraces;
    iis >> openBraces;
    openBraces = strutil::trim( openBraces );

    if ( openBraces != "{" || iis.peek() != EOF )
        return new InterResult( false );

    stringstream ss;
    int lineNumber2 = lineNumber + 1;

    int bracesCount = 1;
    while( it->hasNextLine() && bracesCount > 0 ) {
        string line = it->nextLine();
        int len = line.length();
        for( int i = 0; bracesCount > 0 && i < len; i++ ) {
            switch( line[ i ] ) {
                case '{':
                    bracesCount++;
                    break;
                case '}':
                    bracesCount--;
                    break;
            }

            if ( bracesCount > 0 )
                ss << line[ i ];
        }

        if ( bracesCount > 0 )
            ss << "\n";
        lineNumber2++;
    }

    string blockStr = ss.str();

    vector<string> validCMDs = drv->validCMDNames();

    Task* task = parent->getTask( taskName );
    if ( task == nullptr ) {
        task = new Task( parent );
        task->setName( taskName );

        parent->putTask( task );
    }

    StringIterator* it2 = new StringIterator( blockStr );

    int numberOfLines = 0;
    while( it2->hasNextLine() ) {
        string line = it2->nextLine();
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
            result = manager->interpretsCMD( task, line, currentLineNumber );
        if ( !result->isOk() )
            result = manager->interpretsVar( task, line, currentLineNumber );

        if ( result->isOk() ) {
            numberOfLines += result->getNumberOfLines();
        } else {
            string error;
            if ( result->getErrorMsg() != "" )
                error = result->getErrorMsg();
            else error = "Linha nao reconhecida como comando, propriedade ou variavel.";

            return new InterResult( lineNumber + numberOfLines, error );
        }

        numberOfLines++;
    }

    return new InterResult( task, numberOfLines );
}
