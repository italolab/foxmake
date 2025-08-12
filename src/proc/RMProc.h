#ifndef RM_PROC_H
#define RM_PROC_H

#include "Proc.h"

#include <string>

class RMProc : public Proc {

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
