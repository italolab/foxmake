#ifndef CP_PROC_H
#define CP_PROC_H

#include "Proc.h"
#include "../shell/CMD.h"

class CPProc : public Proc {

    public:
        void proc( CMD* cmd, Config* config );

};

#endif
