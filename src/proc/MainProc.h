#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "Proc.h"
#include "ProcManager.h"
#include "../darv/MainScript.h"
#include "../darv/CMD.h"

#include <string>

using namespace std;

class MainProc : public Proc {

    private:
        void procCMDs( ProcManager* mgr );

        void clean( CMD* cmd, MainScript* script );
        void compileAndLink( CMD* cmd, MainScript* script, bool isCompile, bool isLink );
        void copyFiles( CMD* cmd, MainScript* script );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appDeleteFileOrDirectory( string path );

    public:
        MainProc( string cmdName );

        void processa( CMD* cmd, ProcManager* mgr );

};

#endif
