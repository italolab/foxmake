#ifndef ECHO_PROC_H
#define ECHO_PROC_H

#include "../Exec.h"

#include <string>

class EchoExec : public Exec {

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
