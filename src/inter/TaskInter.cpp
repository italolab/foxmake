
#include "TaskInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "taskconfig/TaskConfigResult.h"
#include "../darv/Task.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* TaskInter::interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    TaskConfigResult* result = manager->interpretsTaskConfig( currentLine );

    int status = result->getStatus();
    if ( status == TaskConfigResult::NO_CONFIG ) {
        return new InterResult( false );
    } else if ( status == TaskConfigResult::ERROR ) {
        return new InterResult( currentLine, 0, 0, result->getErrorMsg() );        
    } 
    
    if ( status != TaskConfigResult::OK )
        throw runtime_error( errors::runtime::INVALID_STATUS_OF_TASK_CONFIG_INTER );    

    if ( result->isFinish() )
        return new InterResult( false );

    string taskName = result->getTaskName();
    vector<string>& flags = result->getFlags();

    for( string flag: flags ) {
        if ( !this->isValidFlag( flag ) ) {
            messagebuilder b( errors::INVALID_TASK_FLAG );
            b << flag;
            
            size_t j = currentLine.find_last_of( flag );
            return new InterResult( currentLine, 0, j, b.str() );
        }
    }

    bool isBefore = this->isBeforeFlag( flags );

    Task* task = parent->getTask( taskName, isBefore );
    if ( task == nullptr ) {
        task = new Task( parent, lineNumber, currentLine );
        task->setName( taskName );

        this->setFlags( task, flags );

        parent->addTask( task );
    }
   
    bool taskendFound = false;
    int numberOfLines = 1;
    while( !taskendFound && it->hasNextLine() ) {
        string line = it->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        if ( line2.length() == 0 ) {
            numberOfLines++;
            continue;
        }

        if ( line2[ 0 ] == '#' ) {
            numberOfLines++;
            continue;
        }

        if ( strutil::trim( line2 ) == "taskend" ) {
            numberOfLines++;
            taskendFound = true;
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
            result = manager->interpretsShellCMD( task, it, line2, currentLineNumber );

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

    if ( !taskendFound )
        return new InterResult( currentLine, 0, 0, errors::END_OF_TASK_BLOCK_NOT_FOUND );

    return new InterResult( task, numberOfLines, 0 );
}

void TaskInter::setFlags( Task* task, vector<string>& flags ) {
    for( string flag : flags ) {
        if ( flag == BEFORE ) {
            task->setBefore( true );
        } else if ( flag == AFTER ) {
            task->setBefore( false );
        }
    }
}

bool TaskInter::isBeforeFlag( vector<string>& flags ) {
    for( string flag : flags )
        if ( flag == "before" )
            return true;
    return false;
}

bool TaskInter::isValidFlag( string flag ) {
    for( string vflag : VALID_FLAGS )
        if ( vflag == flag )
            return true;
    return false;
}