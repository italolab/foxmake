#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "MainScriptInterDriver.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "PropInter.h"
#include "VarInter.h"

class InterManager {

    private:
        MainScriptInter* mainScriptInter;
        CMDInter* cmdInter;
        PropInter* propInter;
        VarInter* varInter;

    public:
        InterManager( MainScriptInterDriver* drv );

        MainScriptInter* getMainScriptInter();
        CMDInter* getCMDInter();
        PropInter* getPropInter();
        VarInter* getVarInter();
};

#endif
