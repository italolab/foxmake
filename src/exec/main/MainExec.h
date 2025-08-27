#ifndef MAIN_EXEC_H
#define MAIN_EXEC_H

#include "../Exec.h"
#include "../../darv/MainScript.h"

class MainExec : public Exec {

    private:
        void configureCMDArgsAndProps( void* mgr );
        void loadMainCMDVariables( void* mgr );
        void genSourceAndHeaderInfos( void* mgr );
        void executaNoDefaultTasks( void* mgr );
        void executaStatements( void* mgr );

        void showHelp( void* mgr );

    public:
        void exec( CMD* cmd, void* mgr );

};

#endif
