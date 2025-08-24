
#include "InterManager.h"

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

InterResult* InterManager::interpretsShellCMD( Block* parent, string line, int lineNumber ) {
    return shellCMDInter->interprets( parent, line, lineNumber, this );
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

void InterManager::interpretsTaskConfig(
                    string& taskName, 
                    vector<string>& flags, 
                    int& status, 
                    string& errorFlag,
                    vector<string>& validFlags,
                    string currentLine,
                    char finalizer ) {

    taskConfigInter->interpretsConfig( taskName, flags, status, errorFlag, validFlags, currentLine, finalizer, this );
}

bool InterManager::isValidCMD( string line ) {
    vector<string> validCMDs = drv->validCMDNames();
    return cmdInter->isValidCMD( line, validCMDs );
}

bool InterManager::isValidProp( string propName ) {
    vector<string> validProps = drv->validPropNames();
    for( string vprop : validProps )
        if ( vprop == propName )
            return true;
    return false;
}
