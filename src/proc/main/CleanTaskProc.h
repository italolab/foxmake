#ifndef CLEAN_TASK_PROC_H
#define CLEAN_TASK_PROC_H

#include "../TaskProc.h"

class CleanTaskProc : public TaskProc {

    private:
        void appRecursiveDeleteFileOrDirectoryIfExists( string path );

    public:
        void proc( CMD* mainCMD, void* mgr );

};

#endif
