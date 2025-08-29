#ifndef MAIN_CMD_ARG_MANAGER_H
#define MAIN_CMD_ARG_MANAGER_H

#include "../darv/GenericCMD.h"

#include <string>

using std::string;

class MainCMDArgManager {

    private:
        void* mgr;

    public:
        MainCMDArgManager( void* mgr );

        bool isHelp();
        bool isVerbose();
        bool isNoResume();

        bool isVerbose( string taskName );
        bool isVerbose( GenericCMD* cmd );
        bool isShowCMDOutput( string taskName );
        bool isShowCMDOutput( GenericCMD* cmd );

        bool isClean();
        bool isCompile();
        bool isCompileAll();
        bool isLink();
        bool isArchive();
        bool isCopy();
        bool isBuild();
        bool isBuildAll();
        bool isArchiveBuild();
        bool isArchiveBuildAll();

};

#endif