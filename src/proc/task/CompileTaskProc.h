#ifndef COMPILE_TASK_PROC_H
#define COMPILE_TASK_PROC_H

#include "../Proc.h"

class CompileTaskProc : public Proc {

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
