#ifndef MKDIR_PROC_H
#define MKDIR_PROC_H

#include "../Proc.h"

#include <string>

class MKDirProc : public Proc {

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
