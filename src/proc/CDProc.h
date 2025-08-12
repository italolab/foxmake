#ifndef CD_PROC_H
#define CD_PROC_H

#include "Proc.h"

#include <string>

class CDProc : public Proc {

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
