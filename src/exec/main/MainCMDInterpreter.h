#ifndef MAIN_CMD_PROCESSOR_H
#define MAIN_CMD_PROCESSOR_H

#include <string>

using std::string;

class MainCMDInterpreter {

    private:
        string workingDir;
        string settingsFile;

        bool workingDirFound;
        bool settingsFileFound;

        void configure( void* mgr );
        void interpretsMainScript( void* mgr );
        void validaMainCMD( void* mgr );

        void loadProperties( void* mgr );
        void loadVariables( void* mgr );

    public:
        MainCMDInterpreter();

        void configureAndInterpretsAndValidate( void* mgr );

};

#endif