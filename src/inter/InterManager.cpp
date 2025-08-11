
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

InterResult* InterManager::interpretsMainCMD( int argc, char* argv[] ) {
    return cmdInter->interpretsMainCMD( argc, argv, this );
}

InterResult* InterManager::interpretsCMD( Block* parent, string cmdstr, int lineNumber ) {
    return cmdInter->interprets( parent, cmdstr, lineNumber, this );
}

InterResult* InterManager::interpretsVar( Block* parent, string line, int lineNumber ) {
    return varInter->interprets( parent, line, lineNumber, this );
}

InterResult* InterManager::interpretsProp( MainScript* parent, string line, int lineNumber ) {
    return propInter->interprets( parent, line, lineNumber, this );
}

InterResult* InterManager::interpretsMainScript( MainScript* script, string file, int lineNumber ) {
    return mainScriptInter->interprets( script, file, lineNumber, this );
}
