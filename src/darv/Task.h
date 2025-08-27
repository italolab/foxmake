#ifndef TASK_H
#define TASK_H

#include "Block.h"

#include <string>

using std::string;

enum class TaskExecution : unsigned int {
    NORMAL = 0,
    BEFORE = 1,
    AFTER = 2
};

class Task : public Block {

    private:
        string name;
        bool verboseFlag;
        bool showCMDOutputFlag;

        TaskExecution taskExecution;

    public:
        Task( Statement* parent, int lineNumber, string line );

        string getName();
        TaskExecution getTaskExecution();

        void setName( string name );
        void setTaskExecution( TaskExecution taskExecution );

};

#endif
