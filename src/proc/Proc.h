#ifndef PROC_H
#define PROC_H

#include "../darv/CMD.h"
#include "../inter/InterResult.h"

class Proc {

    public:
        virtual void proc( CMD* cmd, void* mgr ) = 0;

};

#endif
