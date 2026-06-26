#ifndef DYNAMIC_LIBRARY_LINK_TASK_EXEC_H
#define DYNAMIC_LIBRARY_LINK_TASK_EXEC_H

#include "../TaskExec.h"
#include "TestLinkTaskExec.h"

class DynamicLibraryLinkTaskExec : public TaskExec {

    private:
        TestLinkTaskExec* testLinkTaskExec;
        void execLink( void* mgr );

    public:
        DynamicLibraryLinkTaskExec();
        ~DynamicLibraryLinkTaskExec();

        void exec( void* mgr );

};

#endif