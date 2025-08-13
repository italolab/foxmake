#ifndef CD_PROC_H
#define CD_PROC_H

#include "../Proc.h"

#include <string>

class CDProc : public Proc {

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
