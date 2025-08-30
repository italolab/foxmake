#ifndef COPY_TASK_EXEC_H
#define COPY_TASK_EXEC_H

#include "../TaskExec.h"
#include "../../../darv/MainScript.h"

class CopyTaskExec : public TaskExec {

    private:
        void appCopyFileOrDirectoryToBuild( string path, string buildDir, string propName, void* mgr );

        void appCreateDirs( string dirPath, string propName );

    public:
        void exec( void* mgr );

};

#endif
