#ifndef CD_EXEC_H
#define CD_EXEC_H

#include "../Exec.h"

#include <string>

class CDExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
