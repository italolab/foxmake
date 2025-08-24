
#include "TaskConfigInter.h"
#include "InterManager.h"

#include <sstream>

using std::stringstream;
using std::istringstream;

#include <iostream>
using namespace std;

void TaskConfigInter::interpretsConfig( 
                string& taskName, 
                vector<string>& flags, 
                int& status, 
                string& errorFlag,
                vector<string>& validFlags,
                string currentLine, 
                char finalizer, 
                void* mgr ) {

    size_t i = currentLine.find( finalizer );
    if ( i == string::npos ) {
        status = NO_CONFIG;
        return;
    }                    

    istringstream iis( currentLine );
    bool finalizerFound = false;

    if ( iis.peek() == EOF ) {
        status = NO_CONFIG;
        return;
    }

    iis >> taskName;

    int len = taskName.length();
    if ( len > 0 ) {
        if ( taskName[ len-1 ] == finalizer ) {
            taskName = taskName.substr( 0, len - 1 );
            finalizerFound = true;
        }
    }

    if( !finalizerFound && iis.peek() == EOF ) {
        status = NO_CONFIG;
        return;
    }

    string finalizr = "";
    finalizr += finalizer;

    string flag;
    while( !finalizerFound && iis.peek() != EOF ) {
        iis >> flag;

        bool isFinalizer = ( flag == finalizr );

        int len = flag.length();
        if ( len > 0 ) {
            if ( flag[ len-1 ] == finalizer ) {
                flag = flag.substr( 0, len-1 );
                finalizerFound = true;
            }
        }

        if ( !isFinalizer ) {
            if ( this->isValidFlag( validFlags, flag ) ) {
                flags.push_back( flag );      
            } else {
                errorFlag = flag;
                status = ERROR; 
                return;
            }  
        }
    }

    if ( finalizerFound )
        status = OK;
    else status = NO_CONFIG;
}

bool TaskConfigInter::isValidFlag( vector<string>& validFlags, string flag ) {
    for( string vflag : validFlags )
        if ( vflag == flag )
            return true;
    return false;
}