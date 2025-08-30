
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

#include <iostream>
using namespace std;

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

    string errorMsg;
    bool flagsValid = this->validateFlags( parent, taskName, flags, errorMsg, mgr );
    if ( !flagsValid ) 
        return new InterResult( currentLine, 0, 0, errorMsg );

    Task* task = new Task( parent, lineNumber, currentLine );
    task->setName( taskName );

    this->setFlags( task, flags );

    if ( parent != nullptr )
        parent->addTask( task );
   
    bool taskendFound = false;
    int numberOfLines = 1;
    bool ignoreFlag = false;
    while( !taskendFound && it->hasNextLine() ) {
        string line = it->nextLine();
        string line2 = strutil::removeStartWhiteSpaces( line );

        if ( line2.length() == 0 ) {
            numberOfLines++;
            continue;
        }

        bool ignoreLineFlag = false;

        string line3 = strutil::trim( line );
        if ( line3 == "##" ) {
            ignoreFlag = !ignoreFlag;
            ignoreLineFlag = true;
        } else if ( line2[ 0 ] == '#' ) {
            ignoreLineFlag = true;
        }

        if ( ignoreFlag || ignoreLineFlag ) {
            numberOfLines++;
            continue;
        }

        if ( strutil::trim( line2 ) == "endtask" ) {
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

bool TaskInter::validateFlags( 
            MainScript* script, 
            string taskName, 
            vector<string>& flags, 
            string& errorMsg, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    bool isBefore = false;
    bool isAfter = false;
    for( string flag : flags ) {
        if ( flag == BEFORE ) {
            Task* task = script->getTask( taskName, TaskExecution::BEFORE );
            if ( task != nullptr ) {
                messagebuilder b( errors::TASK_BEFORE_ALREADY_DEFINED );
                b << taskName;
                errorMsg = b.str();
                return false;
            }

            isBefore = true;
        } else if ( flag == AFTER ) {
            Task* task = script->getTask( taskName, TaskExecution::AFTER );
            if ( task != nullptr ) {
                messagebuilder b( errors::TASK_AFTER_ALREADY_DEFINED );
                b << taskName;
                errorMsg = b.str();
                return false;
            }

            isAfter = true;
        }
    }

    if ( isBefore && isAfter ) {
        messagebuilder b( errors::BEFORE_AND_AFTER_TASK );
        b << taskName;
        errorMsg = b.str();
        return false;            
    }

    if ( !isBefore && !isAfter && manager->isValidDefaultTask( taskName ) ) {
        messagebuilder b( errors::DEFAULT_USER_TASK_DEFINED_HOW_NORMAL );
        b << taskName;
        errorMsg = b.str();
        return false;
    }

    return true;
}

void TaskInter::setFlags( Task* task, vector<string>& flags ) {
    bool isBefore = false;
    bool isAfter = false;
    for( string flag : flags ) {
        if ( flag == BEFORE ) {
            task->setTaskExecution( TaskExecution::BEFORE );
            isBefore = true;
        } else if ( flag == AFTER ) {
            task->setTaskExecution( TaskExecution::AFTER );
            isAfter = true;
        }
    }

    if ( !isBefore && !isAfter )
        task->setTaskExecution( TaskExecution::NORMAL );
}

bool TaskInter::isValidFlag( string flag ) {
    for( string vflag : VALID_FLAGS )
        if ( vflag == flag )
            return true;
    return false;
}