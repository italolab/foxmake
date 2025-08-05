#ifndef PROC_H
#define PROC_H

#include "../shell/CMD.h"
#include "../inter/MainInter.h"

class Proc {

    public:
        virtual void proc( CMD* cmd, MainInter* config ) = 0;

};

#endif
