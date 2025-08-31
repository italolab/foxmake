#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "InterDriver.h"
#include "MainScriptInter.h"
#include "TaskInter.h"
#include "DefaultTaskConfigInter.h"
#include "taskconfig/TaskConfigInter.h"
#include "taskconfig/TaskConfigResult.h"
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

        InterResult* interpretsCMD( Block* parent, string line, int& numberOfLinesReaded );
        InterResult* interpretsShellCMD( Block* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded );
        InterResult* interpretsVar( Block* parent, string line, int& numberOfLinesReaded );
        InterResult* interpretsProp( MainScript* parent, string line, int& numberOfLinesReaded );

        InterResult* interpretsMainScript( MainScript* script, string file );
        InterResult* interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int& numberOfLinesReaded );

        InterResult* interpretsDefaultTaskConfig( MainScript* script, string currentLine, int& numberOfLinesReaded );

        TaskConfigResult* interpretsTaskConfig( string currentLine );

        bool isValidCMD( string line );
        bool isValidProp( string propName );
        bool isValidDefaultTask( string taskName );
};

#endif
