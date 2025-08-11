
#include "InterManager.h"
#include "MainScriptInter.h"
#include "CMDInter.h"
#include "VarInter.h"

InterManager::InterManager( BlockInterDriver* drv ) {
    this->mainScriptInter = new MainScriptInter( drv );
    this->cmdInter = new CMDInter();
    this->propInter = new PropInter();
    this->varInter = new VarInter();
}

MainScriptInter* InterManager::getMainScriptInter() {
    return mainScriptInter;
}

CMDInter* InterManager::getCMDInter() {
    return cmdInter;
}

PropInter* InterManager::getPropInter() {
    return propInter;
}

VarInter* InterManager::getVarInter() {
    return varInter;
}
