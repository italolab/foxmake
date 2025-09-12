#ifndef DYNAMIC_LIBRARY_LINK_TASK_EXEC_H
#define DYNAMIC_LIBRARY_LINK_TASK_EXEC_H

#include "../TaskExec.h"

class DynamicLibraryLinkTaskExec : public TaskExec {

    public:
        void exec( void* mgr );

};

#endif