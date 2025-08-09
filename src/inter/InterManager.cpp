
#include "InterManager.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "VarInter.h"

InterManager::InterManager( MainScriptInterDriver* drv ) {
    this->mainScriptInter = new MainScriptInter( drv );
    this->cmdInter = new CMDInter();
    this->varInter = new VarInter();
}

MainScriptInter* InterManager::getMainScriptInter() {
    return mainScriptInter;
}

CMDInter* InterManager::getCMDInter() {
    return cmdInter;
}

VarInter* InterManager::getVarInter() {
    return varInter;
}
