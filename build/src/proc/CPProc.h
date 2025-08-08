#ifndef CP_PROC_H
#define CP_PROC_H

#include "Proc.h"
#include "ProcManager.h"

class CPProc : public Proc {

    public:
        CPProc( string cmdName );

        void processa( CMDInter* inter, ProcManager* mgr );

};

#endif
