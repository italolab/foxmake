#ifndef STATIC_LIBRARY_LINK_TASK_EXEC_H
#define STATIC_LIBRARY_LINK_TASK_EXEC_H

#include "../TaskExec.h"

class StaticLibraryLinkTaskExec : public TaskExec {

    public:
        void exec( void* mgr );

};

#endif