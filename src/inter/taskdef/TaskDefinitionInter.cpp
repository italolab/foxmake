
#include "TaskDefinitionInter.h"
#include "../../util/strutil.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

TaskDefinitionResult* TaskDefinitionInter::interprets( string currentLine, void* mgr ) {
                
    istringstream iss( currentLine );
    string token;

    iss >> token;
    
    if ( token != "task" )
        return new TaskDefinitionResult( TaskDefinitionResult::NO_CONFIG );

    if ( iss.peek() == EOF )
        return new TaskDefinitionResult( errors::TASK_NAME_NOT_DEFINED );    

    string taskName;
    iss >> taskName;

    bool isFinish = false;

    vector<string> flags;

    string flag;
    while( !isFinish && iss.peek() != EOF ) {
        iss >> flag;

        if ( strutil::trim( flag ) == "" )
            continue;

        bool isFinalizer = ( flag == ";" );

        int len = flag.length();
        if ( len > 0 ) {
            if ( flag[ len-1 ] == ';' ) {
                flag = flag.substr( 0, len-1 );
                isFinish = true;
            }
        }

        if ( isFinalizer ) {
            isFinish = true;
        } else {
            flags.push_back( flag );                   
        }
    }

    if ( isFinish ) {
        if ( iss.peek() != EOF ) {
            iss >> token;
            if ( token != "" ) {
                messagebuilder b( errors::UNNECESSARY_TOKEN );
                b << token;
                return new TaskDefinitionResult( b.str() );
            }
        }
    }

    return new TaskDefinitionResult( taskName, flags, isFinish );
}
