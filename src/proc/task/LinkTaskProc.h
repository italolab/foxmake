#ifndef LINK_TASK_PROC_H
#define LINK_TASK_PROC_H

#include "TaskProc.h"

class LinkTaskProc : public TaskProc {

    public:
        void proc( CMD* mainCMD, void* mgr );

};

#endif
