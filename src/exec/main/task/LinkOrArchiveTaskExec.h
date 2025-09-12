#ifndef LINK_TASK_EXEC_H
#define LINK_TASK_EXEC_H

#include "../TaskExec.h"
#include "ExeLinkTaskExec.h"
#include "SharedLibraryLinkTaskExec.h"
#include "ArchiveTaskExec.h"

class LinkOrArchiveTaskExec : public TaskExec {

    private:
        ExeLinkTaskExec* exeLinkTaskExec;
        ArchiveTaskExec* staticLibraryArchiveTaskExec;
        SharedLibraryLinkTaskExec* sharedLibraryLinkTaskExec;

    public:
        LinkOrArchiveTaskExec();
        virtual ~LinkOrArchiveTaskExec();

        void exec( void* mgr );

};

#endif
