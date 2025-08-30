#ifndef TASK_EXEC_H
#define TASK_EXEC_H

class TaskExec {

    public:
        virtual ~TaskExec();

        virtual void exec( void* mgr ) = 0;

};

#endif
