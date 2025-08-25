
#include "TaskConfigResult.h"

TaskConfigResult::TaskConfigResult( string taskName, vector<string>& flags, bool finish ) {
    this->taskName = taskName;
    this->flags = flags;
    this->finish = finish;
    this->status = OK;
}

TaskConfigResult::TaskConfigResult( string errorMsg ) {
    this->errorMsg = errorMsg;
    this->status = ERROR;
}

TaskConfigResult::TaskConfigResult( int status ) {
    this->status = status;
}

string TaskConfigResult::getTaskName() {
    return taskName;
}

vector<string>& TaskConfigResult::getFlags() {
    return flags;
}

int TaskConfigResult::getStatus() {
    return status;
}

string TaskConfigResult::getErrorMsg() {
    return errorMsg;
}

bool TaskConfigResult::isFinish() {
    return finish;
}