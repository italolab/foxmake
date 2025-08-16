#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "../Proc.h"
#include "../../darv/MainScript.h"

class MainProc : public Proc {

    private:
        void genSourceAndHeaderInfos( CMD* mainCMD, void* mgr );
        void executaNoDefaultTasks( void* mgr );
        void executaStatements( void* mgr );

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
