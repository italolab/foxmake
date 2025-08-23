#ifndef CLEAN_TASK_PROC_H
#define CLEAN_TASK_PROC_H

#include "../TaskExec.h"
#include "../../darv/MainScript.h"

class CleanTaskExec : public TaskExec {

    private:
        bool appRecursiveDeleteFileOrDirectoryIfExists( string path, void* mgr );

    public:
        void exec( void* mgr );

};

#endif
