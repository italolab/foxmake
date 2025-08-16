
#include "TaskInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "../darv/Task.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

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
    int numberOfLines0 = 0;

    int bracesCount = 1;
    while( it->hasNextLine() && bracesCount > 0 ) {
        string line = it->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        numberOfLines0++;

        if ( line2.length() == 0 ) {
            ss << "\n";
            continue;
        }

        if ( line2[ 0 ] == '#' ) {
            ss << line << "\n";
            continue;
        }

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

            if ( bracesCount == 0 )
                for( int j = i+1; j < len; j++ )
                    if ( !strutil::isWhiteSpace( line[ j ] ) )
                        return new InterResult( line, numberOfLines0, "Fim de bloco de tarefa com caracteres desnecessarios." );
        }

        if ( bracesCount > 0 )
            ss << line << "\n";
    }

    string blockStr = ss.str();

    Task* task = parent->getTask( taskName );
    if ( task == nullptr ) {
        task = new Task( parent, lineNumber, currentLine );
        task->setName( taskName );

        parent->putTask( task );
    }

    StringIterator* it2 = new StringIterator( blockStr );

    int numberOfLines = 1;
    while( it2->hasNextLine() ) {
        string line = it2->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        if ( line2.length() == 0 ) {
            numberOfLines++;
            continue;
        }

        if ( line2[ 0 ] == '#' ) {
            numberOfLines++;
            continue;
        }

        bool isCmd = manager->isValidCMD( line );

        int currentLineNumber = lineNumber + numberOfLines;

        InterResult* result = new InterResult( false );
        if ( isCmd )
            result = manager->interpretsCMD( task, line2, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsVar( task, line2, currentLineNumber );
        if ( !result->isInterpreted() && !result->isErrorFound() )
            result = manager->interpretsShellCMD( task, line2, currentLineNumber );

        numberOfLines += result->getNumberOfLines();

        if ( !result->isInterpreted() ) {
            string error;
            if ( result->isErrorFound() )
                error = result->getErrorMsg();
            else error = "Linha nao reconhecida como comando, propriedade ou variavel.";

            return new InterResult( result->getLine(), numberOfLines, error );
        }

        delete result;
    }


    numberOfLines++;

    return new InterResult( task, numberOfLines );
}
