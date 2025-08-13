#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "../Proc.h"
#include "../../darv/MainScript.h"

class MainProc : public Proc {

    private:
        void compileAndLink( CMD* cmd, void* manager, bool isCompile, bool isLink );
        void executaNoDefaultTasks( void* mgr );
        void executaCMDs( void* mgr );

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
