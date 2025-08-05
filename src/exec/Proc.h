#ifndef PROC_H
#define PROC_H

#include "../shell/CMD.h"
#include "../config/Config.h"

class Proc {

    public:
        virtual void proc( CMD* cmd, Config* config ) = 0;

};

#endif
