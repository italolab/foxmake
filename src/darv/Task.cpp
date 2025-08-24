
#include "Task.h"
#include "../consts.h"

Task::Task( Statement* parent, int lineNumber, string line ) : Block( parent, lineNumber, line ) {
    this->name = "";
    this->beforeFlag = false;
    this->verboseFlag = false;
    this->showCMDOutputFlag = consts::DEFAULT_SHOW_CMD_OUTPUT;    
}

string Task::getName() {
    return name;
}

bool Task::isBefore() {
    return beforeFlag;
}

void Task::setName( string name ) {
    this->name = name;
}

void Task::setBefore( bool flag ) {
    this->beforeFlag = flag;
}
