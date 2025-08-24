#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "InterDriver.h"
#include "MainScriptInter.h"
#include "TaskInter.h"
#include "DefaultTaskConfigInter.h"
#include "TaskConfigInter.h"
#include "CMDInter.h"
#include "ShellCMDInter.h"
#include "PropInter.h"
#include "VarInter.h"
#include "InterResult.h"
#include "it/BlockIterator.h"

#include "../darv/Block.h"
#include "../darv/MainScript.h"

class InterManager {

    private:
        MainScriptInter* mainScriptInter;
        CMDInter* cmdInter;
        ShellCMDInter* shellCMDInter;
        PropInter* propInter;
        VarInter* varInter;
        TaskInter* taskInter;
        DefaultTaskConfigInter* defaultTaskConfigInter;
        TaskConfigInter* taskConfigInter;

        InterDriver* drv;

    public:
        InterManager( InterDriver* drv );
        virtual ~InterManager();

        InterResult* interpretsMainCMD( int argc, char* argv[] );

        InterResult* interpretsCMD( Block* parent, string line, int lineNumber );
        InterResult* interpretsShellCMD( Block* parent, string line, int lineNumber );
        InterResult* interpretsVar( Block* parent, string line, int lineNumber );
        InterResult* interpretsProp( MainScript* parent, string line, int lineNumber );

        InterResult* interpretsMainScript( MainScript* script, string file, int lineNumber );
        InterResult* interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber );

        InterResult* interpretsDefaultTaskConfig( MainScript* script, string currentLine, int lineNumber );

        void interpretsTaskConfig(
                    string& taskName, 
                    vector<string>& flags, 
                    int& status, 
                    string& errorFlag,
                    vector<string>& validFlags,
                    string currentLine,
                    char finalizer );

        bool isValidCMD( string line );
        bool isValidProp( string propName );
};

#endif
