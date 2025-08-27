#ifndef COMPILE_TASK_EXEC_H
#define COMPILE_TASK_EXEC_H

#include "../TaskExec.h"

#include <string>

using std::string;

class CompileTaskExec : public TaskExec {

    private:
        void appCreateDirs( string dir, void* mgr );

    public:
        void exec( void* mgr );

};

#endif
