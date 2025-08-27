#ifndef ECHO_EXEC_H
#define ECHO_EXEC_H

#include "../Exec.h"

#include <string>

class EchoExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
