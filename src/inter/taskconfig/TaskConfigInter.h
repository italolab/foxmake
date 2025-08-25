#ifndef TASK_CONFIG_INTER_H
#define TASK_CONFIG_INTER_H

#include "TaskConfigResult.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class TaskConfigInter {

    public:        
        TaskConfigResult* interprets( string currentLine, void* mgr );

};

#endif