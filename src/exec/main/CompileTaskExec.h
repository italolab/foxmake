#ifndef COMPILE_TASK_PROC_H
#define COMPILE_TASK_PROC_H

#include "../TaskExec.h"

class CompileTaskExec : public TaskExec {

    private:
        void appCreateDirs( CMD* mainCMD, string dir );

    public:
        void exec( CMD* mainCMD, void* mgr );

};

#endif
