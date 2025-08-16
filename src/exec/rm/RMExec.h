#ifndef RM_PROC_H
#define RM_PROC_H

#include "../Exec.h"

#include <string>

class RMExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
