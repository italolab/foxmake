#ifndef EXE_LINK_TASK_EXEC_H
#define EXE_LINK_TASK_EXEC_H

#include "../TaskExec.h"
#include "../../../sourcecode/SourceCodeManager.h"

class ExeLinkTaskExec : TaskExec {

    private:
        void execLinkage( void* mgr );
        void execTestLinkage( void* mgr );

    public:
        void exec( void* mgr );

};

#endif