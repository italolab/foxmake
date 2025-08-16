#ifndef LINK_TASK_PROC_H
#define LINK_TASK_PROC_H

#include "../TaskExec.h"

class LinkTaskExec : public TaskExec {

    public:
        void exec( CMD* mainCMD, void* mgr );

};

#endif
