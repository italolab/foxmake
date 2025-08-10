#ifndef CD_PROC_H
#define CD_PROC_H

#include "Proc.h"

#include <string>

class CDProc : public Proc {

    public:
        CDProc( string cmdName );

        void processa( CMD* cmd, ProcManager* mgr );

};

#endif
