#ifndef MAIN_CMD_PROCESSOR_H
#define MAIN_CMD_PROCESSOR_H

#include <string>

using std::string;

class MainCMDInterpreter {

    private:
        string workingDir;
        string scriptFile;

        void configure( bool& workingDirFound, bool& scriptFileFound, void* mgr );
        void interpretsMainScript( bool workingDirFound, bool scriptFileFound, void* mgr );
        void validaMainCMD( void* mgr );

        void loadProperties( void* mgr );
        void loadVariables( void* mgr );

    public:
        void configureAndInterpretsAndValidate( void* mgr );

};

#endif