#ifndef ARG_MANAGER_H
#define ARG_MANAGER_H

#include "../darv/GenericCMD.h"

#include <string>

using std::string;

class ArgManager {

    private:
        void* mgr;

    public:
        ArgManager( void* mgr );

        bool isHelp();
        bool isVerbose();
        bool isNoResume();

        bool isVerbose( string taskName );
        bool isVerbose( GenericCMD* cmd );
        bool isShowCMDOutput( string taskName );
        bool isShowCMDOutput( GenericCMD* cmd );

};

#endif