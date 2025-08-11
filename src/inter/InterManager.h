#ifndef INTER_MANAGER_H
#define INTER_MANAGER_H

#include "AbstractInterManager.h"
#include "BlockInterDriver.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "PropInter.h"
#include "VarInter.h"

class InterManager : public AbstractInterManager {

    private:
        MainScriptInter* mainScriptInter;
        CMDInter* cmdInter;
        PropInter* propInter;
        VarInter* varInter;

    public:
        InterManager( BlockInterDriver* drv );

        MainScriptInter* getMainScriptInter();
        CMDInter* getCMDInter();
        PropInter* getPropInter();
        VarInter* getVarInter();
};

#endif
