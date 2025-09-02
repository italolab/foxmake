#ifndef TASK_CONFIG_INTER_H
#define TASK_CONFIG_INTER_H

#include "TaskDefinitionResult.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class TaskDefinitionInter {

    public:        
        TaskDefinitionResult* interprets( string currentLine, void* mgr );

};

#endif