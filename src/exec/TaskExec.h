#ifndef TASK_PROC_H
#define TASK_PROC_H

#include "../darv/CMD.h"

class TaskExec {

    public:
        virtual ~TaskExec();

        virtual void exec( CMD* cmd, void* mgr ) = 0;

};

#endif
