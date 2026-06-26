#ifndef EXE_LINK_TASK_EXEC_H
#define EXE_LINK_TASK_EXEC_H

#include "TestLinkTaskExec.h"

#include "../TaskExec.h"
#include "../../../sourcecode/SourceCodeManager.h"

class ExeLinkTaskExec : TaskExec {

    private:
        TestLinkTaskExec* testLinkTaskExec;

        void execLinkage( void* mgr );

    public:
        ExeLinkTaskExec();
        ~ExeLinkTaskExec();
        
        void exec( void* mgr );

};

#endif