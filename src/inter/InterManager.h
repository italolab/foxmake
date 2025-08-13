#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "InterDriver.h"
#include "MainScriptInter.h"
#include "TaskInter.h"
#include "CMDInter.h"
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
        PropInter* propInter;
        VarInter* varInter;
        TaskInter* taskInter;

        InterDriver* drv;

    public:
        InterManager( InterDriver* drv );

        InterResult* interpretsMainCMD( int argc, char* argv[] );

        InterResult* interpretsCMD( Block* parent, string cmdstr, int lineNumber );
        InterResult* interpretsVar( Block* parent, string line, int lineNumber );
        InterResult* interpretsProp( MainScript* parent, string line, int lineNumber );

        InterResult* interpretsMainScript( MainScript* script, string file, int lineNumber );
        InterResult* interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber );

        bool isValidCMD( string line );
        bool isValidProp( string propName );
};

#endif
