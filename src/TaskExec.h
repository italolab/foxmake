#ifndef TASK_MGR_H
#define TASK_MGR_H

#include "args/Args.h"
#include "util/Properties.h"

class TaskExec {

    private:
        void clean( Args* args, Properties* props );
        void compileAndLink( Args* args, Properties* props, bool isCompile, bool isLink );
        void copyFiles( Args* args, Properties* props );

    public:
        void proc( int argc, char* argv[] );

};

#endif
