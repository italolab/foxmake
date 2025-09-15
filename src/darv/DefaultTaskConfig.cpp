
#include "DefaultTaskConfig.h"
#include "../consts.h"

DefaultTaskConfig::DefaultTaskConfig( Statement* parent, string name, int numberOfLinesReaded, string line ) : Statement( parent, numberOfLinesReaded, line ) {
    this->name = name;
    this->verboseFlag = false;
    this->showCMDOutputFlag = consts::DEFAULT_SHOW_CMD_OUTPUT;

    this->verboseDefinedFlag = false;
    this->showCMDOutputDefinedFlag = false;
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

bool DefaultTaskConfig::isVerboseDefined() {
    return verboseDefinedFlag;
}

bool DefaultTaskConfig::isShowCMDOutputDefined() {
    return showCMDOutputDefinedFlag;
}

void DefaultTaskConfig::setName( string name ) {
    this->name = name;
}

void DefaultTaskConfig::setVerbose( bool flag ) {
    this->verboseFlag = flag;
    this->verboseDefinedFlag = true;
}

void DefaultTaskConfig::setShowCMDOutput( bool flag ) {
    this->showCMDOutputFlag = flag;
    this->showCMDOutputDefinedFlag = true;
}