#ifndef CP_EXEC_H
#define CP_EXEC_H

#include "../Exec.h"

class CPExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
