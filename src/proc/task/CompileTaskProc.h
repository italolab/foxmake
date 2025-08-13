#ifndef COMPILE_TASK_PROC_H
#define COMPILE_TASK_PROC_H

#include "TaskProc.h"

class CompileTaskProc : public TaskProc {

    public:
        void proc( CMD* mainCMD, void* mgr );

};

#endif
