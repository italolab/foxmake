#ifndef CLEAN_TASK_PROC_H
#define CLEAN_TASK_PROC_H

#include "../TaskProc.h"
#include "../../darv/MainScript.h"

class CleanTaskProc : public TaskProc {

    private:
        void appRecursiveDeleteFileOrDirectoryIfExists( string path, string propName, MainScript* script );

    public:
        void proc( CMD* mainCMD, void* mgr );

};

#endif
