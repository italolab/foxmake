#ifndef CD_PROC_H
#define CD_PROC_H

#include "../Exec.h"

#include <string>

class CDExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
