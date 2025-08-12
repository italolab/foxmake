#ifndef COPY_TASK_PROC_H
#define COPY_TASK_PROC_H

#include "../Proc.h"

class CopyTaskProc : public Proc {

    private:
        void appCopyFileOrDirectoryToBuild( string path, string buildDir );


    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
