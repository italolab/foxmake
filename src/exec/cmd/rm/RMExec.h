#ifndef RM_EXEC_H
#define RM_EXEC_H

#include "../ExecCMD.h"

#include <string>

class RMExec {

    public:
        void exec( ExecCMD* execCMD, void* mgr );

};

#endif
