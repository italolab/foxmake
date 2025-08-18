#ifndef COPY_TASK_PROC_H
#define COPY_TASK_PROC_H

#include "../TaskExec.h"
#include "../../darv/MainScript.h"

class CopyTaskExec : public TaskExec {

    private:
        void appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, MainScript* script );

        void appCreateDirs( CMD* mainCMD, string dirPath, string propName );

    public:
        void exec( CMD* mainCMD, void* mgr );

};

#endif
