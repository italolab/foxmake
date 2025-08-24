
#include "DefaultTaskConfigInter.h"
#include "InterManager.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

InterResult* DefaultTaskConfigInter::interprets( MainScript* parent, string currentLine, int lineNumber, void* mgr ) {
    InterManager* manager = (InterManager*)mgr;

    int status = TaskConfigInter::NO_CONFIG;
    string taskName;
    string errorFlag;
    vector<string> flags;
    char finalizer = ';';

    vector<string>& validFlagsVect = VALID_FLAGS;

    manager->interpretsTaskConfig( taskName, flags, status, errorFlag, validFlagsVect, currentLine, finalizer );

    if ( status == TaskConfigInter::OK ) {
        if ( !manager->isValidDefaultTask( taskName ) ) {
            messagebuilder b( errors::IS_NOT_A_DEFAULT_TASK );
            b << taskName;
            return new InterResult( currentLine, 0, 0, b.str() );
        }

        DefaultTaskConfig* config = parent->getDefaultTaskConfig( taskName );
        if ( config == nullptr )
            config = new DefaultTaskConfig( parent, taskName, lineNumber, currentLine );
        
        this->setFlags( config, flags );

        if ( parent != nullptr )
            parent->addDefaultTaskConfig( config );

        return new InterResult( config, 1, currentLine.length() );
    } else if ( status == TaskConfigInter::ERROR ) {
        messagebuilder b( errors::INVALID_TASK_FLAG );
        b << errorFlag;

        size_t j = currentLine.find( errorFlag );
        if ( j == string::npos )
            j = 0;

        return new InterResult( currentLine, 0, (int)j, b.str() );
    } else {
        return new InterResult( false );
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