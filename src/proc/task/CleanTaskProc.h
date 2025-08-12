#ifndef CLEAN_TASK_PROC_H
#define CLEAN_TASK_PROC_H

#include "../Proc.h"

class CleanTaskProc : public Proc {

    private:
        void appRecursiveDeleteFileOrDirectoryIfExists( string path );

    public:
        void processa( CMD* cmd, ProcManager* manager );

};

#endif
