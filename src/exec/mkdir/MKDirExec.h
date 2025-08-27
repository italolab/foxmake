#ifndef MKDIR_EXEC_H
#define MKDIR_EXEC_H

#include "../Exec.h"

#include <string>

class MKDirExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
