#ifndef CP_PROC_H
#define CP_PROC_H

#include "../Proc.h"

class CPProc : public Proc {

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
