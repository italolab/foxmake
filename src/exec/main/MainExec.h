#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "../Exec.h"
#include "../../darv/MainScript.h"

class MainExec : public Exec {

    private:
        void genSourceAndHeaderInfos( CMD* mainCMD, void* mgr );
        void executaNoDefaultTasks( void* mgr );
        void executaStatements( void* mgr );

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
