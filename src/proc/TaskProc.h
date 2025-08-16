#ifndef TASK_PROC_H
#define TASK_PROC_H

#include "../darv/CMD.h"

class TaskProc {

    public:
        virtual ~TaskProc();

        virtual void proc( CMD* cmd, void* mgr ) = 0;

};

#endif
