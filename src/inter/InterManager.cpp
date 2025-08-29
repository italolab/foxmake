
#include "InterManager.h"
#include "../util/strutil.h"

InterManager::InterManager( InterDriver* drv ) {
    this->drv = drv;

    this->mainScriptInter = new MainScriptInter();
    this->taskInter = new TaskInter();
    this->taskConfigInter = new TaskConfigInter();
    this->defaultTaskConfigInter = new DefaultTaskConfigInter();
    this->cmdInter = new CMDInter();
    this->shellCMDInter = new ShellCMDInter();
    this->propInter = new PropInter();
    this->varInter = new VarInter();
}

InterManager::~InterManager() {
    delete mainScriptInter;
    delete taskInter;
    delete taskConfigInter;
    delete defaultTaskConfigInter;
    delete cmdInter;
    delete shellCMDInter;
    delete propInter;
    delete varInter;
}

InterResult* InterManager::interpretsMainCMD( int argc, char* argv[] ) {
    return cmdInter->interpretsMainCMD( argc, argv, this );
}

InterResult* InterManager::interpretsCMD( Block* parent, string line, int lineNumber ) {
    return cmdInter->interprets( parent, line, lineNumber, this );
}

InterResult* InterManager::interpretsShellCMD( Block* parent, BlockIterator* it, string currentLine, int lineNumber ) {
    return shellCMDInter->interprets( parent, it, currentLine, lineNumber, this );
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

InterResult* InterManager::interpretsTask( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber ) {
    return taskInter->interprets( parent, it, currentLine, lineNumber, this );
}

InterResult* InterManager::interpretsDefaultTaskConfig( MainScript* script, string currentLine, int lineNumber ) {
    return defaultTaskConfigInter->interprets( script, currentLine, lineNumber, this );
}

TaskConfigResult* InterManager::interpretsTaskConfig( string currentLine ) {
    return taskConfigInter->interprets( currentLine, this );
}

bool InterManager::isValidCMD( string line ) {
    string line2 = strutil::removeStartWhiteSpaces( line );
    size_t i = line2.find( ' ' );
    if ( i != string::npos ) {
        string cmd = line2.substr( 0, i );
        return drv->isValidCMD( cmd );
    }

    return false;
}

bool InterManager::isValidProp( string propName ) {
   return drv->isValidProp( propName );
}

bool InterManager::isValidDefaultTask( string taskName ) {
    return drv->isDefaultTask( taskName );
}
