#ifndef LINK_TASK_EXEC_H
#define LINK_TASK_EXEC_H

#include "../TaskExec.h"
#include "ExeLinkTaskExec.h"
#include "DynamicLibraryLinkTaskExec.h"
#include "ArchiveTaskExec.h"

class LinkTaskExec : public TaskExec {

    private:
        ExeLinkTaskExec* exeLinkTaskExec;
        ArchiveTaskExec* staticLibraryArchiveTaskExec;
        DynamicLibraryLinkTaskExec* dynamicLibraryLinkTaskExec;

    public:
        LinkTaskExec();
        virtual ~LinkTaskExec();

        void exec( void* mgr );

};

#endif
