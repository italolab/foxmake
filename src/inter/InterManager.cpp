
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

InterResult* InterManager::interpretsCMD( Block* block, string cmdstr, int lineNumber ) {
    return cmdInter->interprets( block, cmdstr, lineNumber, this );
}

InterResult* InterManager::interpretsVar( Block* block, string line, int lineNumber ) {
    return varInter->interprets( block, line, lineNumber, this );
}

InterResult* InterManager::interpretsProp( MainScript* script, string line, int lineNumber ) {
    return propInter->interprets( script, line, lineNumber, this );
}

InterResult* InterManager::interpretsMainScript( string file, int lineNumber ) {
    return mainScriptInter->interprets( file, lineNumber, this );
}
