#ifndef CP_PROC_H
#define CP_PROC_H

#include "../Exec.h"

class CPExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
