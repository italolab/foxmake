#ifndef CALL_EXEC_H
#define CALL_EXEC_H

#include "../Exec.h"

#include <string>

class CallExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif