#ifndef LINK_TASK_EXEC_H
#define LINK_TASK_EXEC_H

#include "../TaskExec.h"
#include "ExeLinkTaskExec.h"
#include "StaticLibraryLinkTaskExec.h"
#include "DynamicLibraryLinkTaskExec.h"

class LinkTaskExec : public TaskExec {

    private:
        ExeLinkTaskExec* exeLinkTaskExec;
        StaticLibraryLinkTaskExec* staticLibraryLinkTaskExec;
        DynamicLibraryLinkTaskExec* dynamicLibraryLinkTaskExec;

    public:
        LinkTaskExec();

        void exec( void* mgr );

};

#endif
