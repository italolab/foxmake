
#include "TaskInter.h"
#include "InterManager.h"
#include "it/StringIterator.h"
#include "taskdef/TaskDefinitionResult.h"
#include "../darv/Task.h"
#include "../util/strutil.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

TaskInter::~TaskInter() {}

InterResult* TaskInter::interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {
    return new InterResult( false );
}

/*
O atributo endTokenNotFoundIResult é carregado dentro da função interprets. Logo, 
depende dela para não ser nulo.
*/
InterResult* TaskInter::interprets( 
            MainScript* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    TaskDefinitionResult* result = manager->interpretsTaskDefinition( currentLine );

    int status = result->getStatus();
    if ( status == TaskDefinitionResult::NO_CONFIG ) {
        return new InterResult( false );
    } else if ( status == TaskDefinitionResult::HAS_ERROR ) {
        return new InterResult( currentLine, numberOfLinesReaded, 0, result->getErrorMsg() );        
    } 
    
    if ( status != TaskDefinitionResult::OK )
        throw runtime_error( errors::runtime::INVALID_STATUS_OF_TASK_CONFIG_INTER );    

    if ( result->isFinish() )
        return new InterResult( false );

    string taskName = result->getTaskName();
    vector<string>& flags = result->getFlags();

    InterResult* endTokenNotFoundIResult = new InterResult( currentLine, numberOfLinesReaded, 0, errors::END_OF_TASK_BLOCK_NOT_FOUND );

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
       
    string endToken = "endtask";
    InterResult* blockIResult = BlockInter::interpretsBlock( 
                task, it, numberOfLinesReaded, endToken, endTokenNotFoundIResult, mgr );
                
    if ( blockIResult->isErrorFound() )
        return blockIResult;
    
    return new InterResult( task, numberOfLinesReaded, 0 );
}

/*
Nesta médodo é feita a validação das flags da configuração da tarefa. 
Exemplo:
    task init a;
    essa task está sendo configurada com uma flag que não é nem before e nem after.

    task init;
    Esta task está sendo configurada como normal com o flag omitido, mas ela é uma 
    task default e não pode ser definida como normal.

    task compile before after;
    Tarefa definida como before e after. Isso não é permitido!

    task compile before;
    task compile before;
    A segunda configuração da task compile tem o before que já foi definido na primeira 
    configuração.
*/
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