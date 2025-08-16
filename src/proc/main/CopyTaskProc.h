#ifndef COPY_TASK_PROC_H
#define COPY_TASK_PROC_H

#include "../TaskProc.h"
#include "../../darv/MainScript.h"

class CopyTaskProc : public TaskProc {

    private:
        void appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, MainScript* script );

        void appCreateDirs( CMD* mainCMD, string dirPath );

    public:
        void proc( CMD* mainCMD, void* mgr );

};

#endif
