#ifndef MAIN_EXEC_H
#define MAIN_EXEC_H

#include "MainCMDInterpreter.h"
#include "task/CleanTaskExec.h"
#include "task/CompileTaskExec.h"
#include "task/LinkOrArchiveTaskExec.h"
#include "task/TestTaskExec.h"
#include "task/CopyTaskExec.h"
#include "../../darv/CMD.h"
#include "../../darv/MainScript.h"

class MainExec {

    private:
        MainCMDInterpreter* mainCMDInterpreter;

        CleanTaskExec* cleanTaskExec;
        CompileTaskExec* compileTaskExec;
        LinkOrArchiveTaskExec* linkOrArchiveTaskExec;
        TestTaskExec* testTaskExec;
        CopyTaskExec* copyTaskExec;

        void genSourceAndHeaderInfos( void* mgr );
        void executaNoDefaultTasks( void* mgr );
        void executaStatements( void* mgr );

        void showHelp( void* mgr );

    public:
        MainExec();
        virtual ~MainExec();
        
        void exec( CMD* cmd, void* mgr );

};

#endif
