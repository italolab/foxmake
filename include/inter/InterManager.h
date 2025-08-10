#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "MainScriptInterDriver.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "VarInter.h"

class InterManager {

    private:
        MainScriptInter* mainScriptInter;
        CMDInter* cmdInter;
        VarInter* varInter;

    public:
        InterManager( MainScriptInterDriver* drv );

        MainScriptInter* getMainScriptInter();
        CMDInter* getCMDInter();
        VarInter* getVarInter();
};

#endif
