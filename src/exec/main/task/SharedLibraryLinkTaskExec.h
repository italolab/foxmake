#ifndef SHARED_LIBRARY_LINK_TASK_EXEC_H
#define SHARED_LIBRARY_LINK_TASK_EXEC_H

#include "../TaskExec.h"

class SharedLibraryLinkTaskExec : public TaskExec {

    public:
        void exec( void* mgr );

};

#endif