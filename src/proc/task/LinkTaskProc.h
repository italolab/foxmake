#ifndef LINK_TASK_PROC_H
#define LINK_TASK_PROC_H

#include "../Proc.h"

class LinkTaskProc : public Proc {

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
