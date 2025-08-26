#ifndef LINK_TASK_PROC_H
#define LINK_TASK_PROC_H

#include "../TaskExec.h"
#include "ExeLinkTaskExec.h"
#include "DynamicLibraryLinkTaskExec.h"

class LinkTaskExec : public TaskExec {

    private:
        ExeLinkTaskExec* exeLinkTaskExec;
        DynamicLibraryLinkTaskExec* dynamicLibraryLinkTaskExec;

    public:
        LinkTaskExec();

        void exec( void* mgr );

};

#endif
