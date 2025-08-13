#ifndef TASK_PROC_H
#define TASK_PROC_H

#include "../darv/CMD.h"

#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

class taskproc_error : public runtime_error {

    private:
        Statement* st;

    public:
        taskproc_error( string msg );
        taskproc_error( Statement* st, string msg );

        string message() const;

};

class TaskProc {

    public:
        virtual void proc( CMD* cmd, void* mgr ) = 0;

};

#endif
