#ifndef RM_EXEC_H
#define RM_EXEC_H

#include "../Exec.h"

#include <string>

class RMExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
