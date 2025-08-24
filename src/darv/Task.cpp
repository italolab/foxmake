
#include "Task.h"

Task::Task( Statement* parent, int lineNumber, string line ) : Block( parent, lineNumber, line ) {
    this->name = "";
    this->beforeFlag = false;
    this->verboseFlag = false;
    this->showOutputFlag = false;    
}

string Task::getName() {
    return name;
}

bool Task::isBefore() {
    return beforeFlag;
}

bool Task::isVerbose() {
    return verboseFlag;
}

bool Task::isShowOutput() {
    return showOutputFlag;
}

void Task::setName( string name ) {
    this->name = name;
}

void Task::setBefore( bool flag ) {
    this->beforeFlag = flag;
}

void Task::setVerbose( bool flag ) {
    this->verboseFlag = flag;
}

void Task::setShowOutput( bool flag ) {
    this->showOutputFlag = flag;
}
