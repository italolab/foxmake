#ifndef ECHO_PROC_H
#define ECHO_PROC_H

#include "Proc.h"

#include <string>

class EchoProc : public Proc {

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
