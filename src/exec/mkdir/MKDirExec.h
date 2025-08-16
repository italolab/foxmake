#ifndef MKDIR_PROC_H
#define MKDIR_PROC_H

#include "../Exec.h"

#include <string>

class MKDirExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
