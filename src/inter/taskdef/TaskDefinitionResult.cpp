
#include "TaskDefinitionResult.h"

TaskDefinitionResult::TaskDefinitionResult( string taskName, vector<string>& flags, bool finish ) {
    this->taskName = taskName;
    this->flags = flags;
    this->finish = finish;
    this->status = OK;
}

TaskDefinitionResult::TaskDefinitionResult( string errorMsg ) {
    this->errorMsg = errorMsg;
    this->status = ERROR;
}

TaskDefinitionResult::TaskDefinitionResult( int status ) {
    this->status = status;
}

string TaskDefinitionResult::getTaskName() {
    return taskName;
}

vector<string>& TaskDefinitionResult::getFlags() {
    return flags;
}

int TaskDefinitionResult::getStatus() {
    return status;
}

string TaskDefinitionResult::getErrorMsg() {
    return errorMsg;
}

bool TaskDefinitionResult::isFinish() {
    return finish;
}