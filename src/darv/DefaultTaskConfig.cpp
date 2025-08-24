
#include "DefaultTaskConfig.h"
#include "../consts.h"

DefaultTaskConfig::DefaultTaskConfig( Statement* parent, string name, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
    this->name = name;
    this->verboseFlag = false;
    this->showCMDOutputFlag = consts::DEFAULT_SHOW_CMD_OUTPUT;
}

string DefaultTaskConfig::getName() {
    return name;
}

bool DefaultTaskConfig::isVerbose() {
    return verboseFlag;
}

bool DefaultTaskConfig::isShowCMDOutput() {
    return showCMDOutputFlag;
}

void DefaultTaskConfig::setName( string name ) {
    this->name = name;
}

void DefaultTaskConfig::setVerbose( bool flag ) {
    this->verboseFlag = flag;
}

void DefaultTaskConfig::setShowCMDOutput( bool flag ) {
    this->showCMDOutputFlag = flag;
}