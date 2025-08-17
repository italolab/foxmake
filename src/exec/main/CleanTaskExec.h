#ifndef CLEAN_TASK_PROC_H
#define CLEAN_TASK_PROC_H

#include "../TaskExec.h"
#include "../../darv/MainScript.h"

class CleanTaskExec : public TaskExec {

    private:
        bool appRecursiveDeleteFileOrDirectoryIfExists( string path, MainScript* script );

    public:
        void exec( CMD* mainCMD, void* mgr );

};

#endif
