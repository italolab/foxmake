
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

/*
Nesta classe é feita, também, a validação das flags da configuração da tarefa. 
Exemplo:
    task init a;
    essa task está sendo configurada com uma flag que não é, nem before e nem after.

    task init;
    Esta task está sendo configurada como normal com o flag omitido, mas ela é uma 
    task default e não pode ser definida como normal.

    task compile before after;
    Tarefa definida como before e after.

    task compile before;
    task compile before after;
    A segunda configuração da task compile tem o before que já foi definido na primeira 
    configuração.
*/

TaskInter::~TaskInter() {}

InterResult* TaskInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {
    return new InterResult( false );
}

InterResult* TaskInter::interpretsEnd( 
            Block* block, string currentLine, int& numberOfLinesReaded ) {

    istringstream iss( currentLine );
    if ( iss.peek() == EOF )
        return new InterResult( false );

    string token;
    iss >> token;
    if ( token == "endtask" ) {
        if ( iss.peek() == EOF )
            return new InterResult( true );

        iss >> token;
        if ( token != "" ) {
            messagebuilder b( errors::UNNECESSARY_TOKEN );
            b << token;
            return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );        
        }
    };

    return new InterResult( false );
}

InterResult* TaskInter::interprets( 
            MainScript* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    TaskConfigResult* result = manager->interpretsTaskConfig( currentLine );

    int status = result->getStatus();
    if ( status == TaskConfigResult::NO_CONFIG ) {
        return new InterResult( false );
    } else if ( status == TaskConfigResult::ERROR ) {
        return new InterResult( currentLine, numberOfLinesReaded, 0, result->getErrorMsg() );        
    } 
    
    if ( status != TaskConfigResult::OK )
        throw runtime_error( errors::runtime::INVALID_STATUS_OF_TASK_CONFIG_INTER );    

    if ( result->isFinish() )
        return new InterResult( false );

    string taskName = result->getTaskName();
    vector<string>& flags = result->getFlags();

    string errorMsg;

    bool flagsValid = this->validateFlags( 
                parent, 
                taskName, 
                flags, 
                errorMsg, 
                currentLine, 
                mgr );

    if ( !flagsValid ) 
        return new InterResult( currentLine, numberOfLinesReaded, 0, errorMsg );

    numberOfLinesReaded++;

    Task* task = new Task( parent, numberOfLinesReaded, currentLine );
    task->setName( taskName );

    this->setFlags( task, flags );

    if ( parent != nullptr )
        parent->addTask( task );
       
    BlockInterResult* blockIResult = BlockInter::interpretsBlock( task, it, numberOfLinesReaded, mgr );
    InterResult* iresult = blockIResult->getInterResult();
    if ( !blockIResult->isEndFound() ) {       
        if ( iresult->isErrorFound() )
            return iresult;
        return new InterResult( currentLine, numberOfLinesReaded, 0, errors::END_OF_TASK_BLOCK_NOT_FOUND );
    }
    return new InterResult( task, numberOfLinesReaded, 0 );
}

bool TaskInter::validateFlags( 
            MainScript* script, 
            string taskName, 
            vector<string>& flags, 
            string& errorMsg, 
            string currentLine,
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    bool isBefore = false;
    bool isAfter = false;
    for( string flag : flags ) {
        if ( !this->isValidFlag( flag ) ) {
            messagebuilder b( errors::INVALID_TASK_FLAG );
            b << flag;            
            errorMsg = b.str();
            return false;
        }

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