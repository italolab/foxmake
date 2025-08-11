#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "BlockInterDriver.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "PropInter.h"
#include "VarInter.h"
#include "InterResult.h"

#include "../darv/Block.h"
#include "../darv/MainScript.h"

class InterManager {

    private:
        MainScriptInter* mainScriptInter;
        CMDInter* cmdInter;
        PropInter* propInter;
        VarInter* varInter;

    public:
        InterManager( BlockInterDriver* drv );

        InterResult* interpretsMainCMD( int argc, char* argv[] );

        InterResult* interpretsCMD( Block* parent, string cmdstr, int lineNumber );
        InterResult* interpretsVar( Block* parent, string line, int lineNumber );
        InterResult* interpretsProp( MainScript* parent, string line, int lineNumber );

        InterResult* interpretsMainScript( MainScript* script, string file, int lineNumber );

};

#endif
