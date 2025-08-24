
#include "TaskInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "../darv/Task.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* TaskInter::interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    int status = TaskConfigInter::NO_CONFIG;
    string taskName;
    string errorFlag;
    vector<string> flags;
    char finalizer = '{';

    vector<string>& validFlagsVect = VALID_FLAGS;

    manager->interpretsTaskConfig( taskName, flags, status, errorFlag, validFlagsVect, currentLine, finalizer );

    if ( status == TaskConfigInter::ERROR ) {
        messagebuilder b( errors::INVALID_TASK_FLAG );
        b << errorFlag;

        size_t j = currentLine.find( errorFlag );
        if ( j == string::npos )
            j = 0;

        return new InterResult( currentLine, 0, (int)j, b.str() );            
    } else if ( status == TaskConfigInter::NO_CONFIG ) {
        return new InterResult( false );
    }

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
                        return new InterResult( line, numberOfLines0, 0, errors::END_OF_BLOCK_WITH_UNNECESSARY_CHARACTERS );
        }

        if ( bracesCount > 0 )
            ss << line << "\n";
    }

    string blockStr = ss.str();

    bool isBefore = this->isBeforeFlag( flags );
   
    Task* task = parent->getTask( taskName, isBefore );
    if ( task == nullptr ) {
        task = new Task( parent, lineNumber, currentLine );
        task->setName( taskName );

        this->setFlags( task, flags );

        parent->addTask( task );
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
            string resultLine;
            if ( result->isErrorFound() ) {
                error = result->getErrorMsg();
                resultLine = result->getLine();
            } else {
                error = errors::UNRECOGNIZED_LINE;
                resultLine = line;
            }

            return new InterResult( resultLine, numberOfLines, 0, error );
        }

        delete result;
    }


    numberOfLines++;

    return new InterResult( task, numberOfLines, 0 );
}

void TaskInter::setFlags( Task* task, vector<string>& flags ) {
    for( string flag : flags ) {
        if ( flag == "before" ) {
            task->setBefore( true );
        } else if ( flag == "after" ) {
            task->setBefore( false );
        } else if ( flag == "verbose" ) {
            task->setVerbose( true );
        } else if ( flag == "noverbose" ) {
            task->setVerbose( false );
        } else if ( flag == "showoutput" ) {
            task->setShowOutput( true );
        } else if ( flag == "noshowoutput" ) {
            task->setShowOutput( false );
        }
    }
}

bool TaskInter::isBeforeFlag( vector<string>& flags ) {
    for( string flag : flags )
        if ( flag == "before" )
            return true;
    return false;
}