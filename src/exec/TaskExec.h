#ifndef TASK_PROC_H
#define TASK_PROC_H

class TaskExec {

    public:
        virtual ~TaskExec();

        virtual void exec( void* mgr ) = 0;

};

#endif
