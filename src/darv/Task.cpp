
#include "Task.h"
#include "../consts.h"

Task::Task( Statement* parent, int lineNumber, string line ) : Block( parent, lineNumber, line ) {
    this->name = "";
    this->taskExecution = TaskExecution::NORMAL;
    this->verboseFlag = false;
    this->showCMDOutputFlag = consts::DEFAULT_SHOW_CMD_OUTPUT;    
}

string Task::getName() {
    return name;
}

TaskExecution Task::getTaskExecution() {
    return taskExecution;
}

void Task::setName( string name ) {
    this->name = name;
}

void Task::setTaskExecution( TaskExecution taskExecution ) {
    this->taskExecution = taskExecution;
}
