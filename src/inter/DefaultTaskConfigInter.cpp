
#include "DefaultTaskConfigInter.h"
#include "taskdef/TaskDefinitionResult.h"
#include "InterManager.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* DefaultTaskConfigInter::interprets( 
            MainScript* parent, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr ) {

    InterManager* manager = (InterManager*)mgr;

    TaskDefinitionResult* result = manager->interpretsTaskDefinition( currentLine );
    
    int status = result->getStatus();
    if ( status == TaskDefinitionResult::OK ) {  
        if ( !result->isFinish() )
            return new InterResult( false );

        numberOfLinesReaded++;

        string taskName = result->getTaskName();
        vector<string>& flags = result->getFlags();

        if ( !manager->isValidDefaultTask( taskName ) ) {
            messagebuilder b( errors::IS_NOT_A_DEFAULT_TASK );
            b << taskName;
            return new InterResult( currentLine, numberOfLinesReaded, 0, b.str() );
        }

        for( string flag: flags ) {
            if ( !this->isValidFlag( flag ) ) {
                messagebuilder b( errors::INVALID_TASK_FLAG );
                b << flag;
                
                size_t j = currentLine.find_last_of( flag );
                return new InterResult( currentLine, numberOfLinesReaded, j, b.str() );
            }
        }

        DefaultTaskConfig* config = parent->getDefaultTaskConfig( taskName );
        if ( config == nullptr )
            config = new DefaultTaskConfig( parent, taskName, numberOfLinesReaded, currentLine );
        
        this->setFlags( config, flags );

        if ( parent != nullptr )
            parent->addDefaultTaskConfig( config );

        return new InterResult( config, numberOfLinesReaded, currentLine.length() );
    } else if ( status == TaskDefinitionResult::HAS_ERROR ) {
        string errorMsg = result->getErrorMsg();
        return new InterResult( currentLine, numberOfLinesReaded, 0, errorMsg );        
    } else if ( status == TaskDefinitionResult::NO_CONFIG ) {
        return new InterResult( false );
    } else {
        throw runtime_error( errors::runtime::INVALID_STATUS_OF_TASK_CONFIG_INTER );
    }
}

void DefaultTaskConfigInter::setFlags( DefaultTaskConfig* config, vector<string>& flags ) {
    for( string flag : flags ) {
        if ( flag == VERBOSE ) {
            config->setVerbose( true );
        } else if ( flag == NOVERBOSE ) {
            config->setVerbose( false );
        } else if ( flag == SHOWOUTPUT ) {
            config->setShowCMDOutput( true );
        } else if ( flag == NOSHOWOUTPUT ) {
            config->setShowCMDOutput( false );
        }
    }
}

bool DefaultTaskConfigInter::isValidFlag( string flag ) {
    for( string vflag : VALID_FLAGS )
        if ( vflag == flag )
            return true;
    return false;
}