#ifndef MAIN_EXEC_H
#define MAIN_EXEC_H

#include "../Exec.h"
#include "../../darv/MainScript.h"

class MainExec : public Exec {

    private:
        void genSourceAndHeaderInfos( CMD* mainCMD, void* mgr );
        void executaNoDefaultTasks( CMD* mainCMD, void* mgr );
        void executaStatements( void* mgr );

        void showHelp( CMD* mainCMD, void* mgr );

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
