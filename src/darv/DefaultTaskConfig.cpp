
#include "DefaultTaskConfig.h"

DefaultTaskConfig::DefaultTaskConfig( Statement* parent, string name, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
    this->name = name;
    this->verboseFlag = false;
    this->showOutputFlag = true;
}

string DefaultTaskConfig::getName() {
    return name;
}

bool DefaultTaskConfig::isVerbose() {
    return verboseFlag;
}

bool DefaultTaskConfig::isShowOutput() {
    return showOutputFlag;
}

void DefaultTaskConfig::setName( string name ) {
    this->name = name;
}

void DefaultTaskConfig::setVerbose( bool flag ) {
    this->verboseFlag = flag;
}

void DefaultTaskConfig::setShowOutput( bool flag ) {
    this->showOutputFlag = flag;
}