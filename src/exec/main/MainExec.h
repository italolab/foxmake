#ifndef MAIN_EXEC_H
#define MAIN_EXEC_H

#include "CleanTaskExec.h"
#include "CompileTaskExec.h"
#include "LinkOrArchiveTaskExec.h"
#include "CopyTaskExec.h"
#include "../Exec.h"
#include "../../darv/MainScript.h"

class MainExec : public Exec {

    private:
        CleanTaskExec* cleanTaskExec;
        CompileTaskExec* compileTaskExec;
        LinkOrArchiveTaskExec* linkOrArchiveTaskExec;
        CopyTaskExec* copyTaskExec;

        void validaMainCMD( void* mgr );
        void configureMainCMDArgsAndProps( void* mgr );
        void loadMainCMDProperties( void* mgr );
        void loadMainCMDVariables( void* mgr );
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
