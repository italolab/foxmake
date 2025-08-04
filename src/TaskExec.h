#ifndef TASK_MGR_H
#define TASK_MGR_H

#include "Args.h"
#include "ArgsInter.h"
#include "Properties.h"

class TaskExec {

    private:
        void clean( Args* args, Properties* props );
        void compile( Args* args, Properties* props );
        void link( Args* args, Properties* props );

    public:
        void proc( int argc, char* argv[] );

};

#endif
