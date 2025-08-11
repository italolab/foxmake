#ifndef ECHO_PROC_H
#define ECHO_PROC_H

#include "Proc.h"

#include <string>

class EchoProc : public Proc {

    public:
        EchoProc( string cmdName );

        void processa( CMD* cmd, ProcManager* manager );

};

#endif
