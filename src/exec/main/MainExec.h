#ifndef MAIN_EXEC_H
#define MAIN_EXEC_H

#include "task/CleanTaskExec.h"
#include "task/CompileTaskExec.h"
#include "task/LinkOrArchiveTaskExec.h"
#include "task/TestTaskExec.h"
#include "task/CopyTaskExec.h"
#include "../Exec.h"
#include "../../darv/MainScript.h"

class MainExec : public Exec {

    private:
        CleanTaskExec* cleanTaskExec;
        CompileTaskExec* compileTaskExec;
        LinkOrArchiveTaskExec* linkOrArchiveTaskExec;
        TestTaskExec* testTaskExec;
        CopyTaskExec* copyTaskExec;

        void validaMainCMD( void* mgr );
        void configureEnvironmentAndInterpretsMainScript( void* mgr );
        void genSourceAndHeaderInfos( void* mgr );
        void executaNoDefaultTasks( void* mgr );
        void executaStatements( void* mgr );

        void loadMainCMDProperties( void* mgr );
        void loadMainCMDVariables( void* mgr );

        void showHelp( void* mgr );

    public:
        MainExec();
        virtual ~MainExec();
        
        void exec( CMD* cmd, void* mgr );

};

#endif
