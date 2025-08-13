#ifndef RM_PROC_H
#define RM_PROC_H

#include "../Proc.h"

#include <string>

class RMProc : public Proc {

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
