#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "Proc.h"
#include "ProcManager.h"
#include "../cmd/CMD.h"
#include "../inter/MainInter.h"

#include <string>

using namespace std;

class MainProc : public Proc {

    private:
        void procCMDs( ProcManager* mgr );

        void clean( CMD* cmd, MainInter* inter );
        void compileAndLink( CMD* cmd, MainInter* inter, bool isCompile, bool isLink );
        void copyFiles( CMD* cmd, MainInter* inter );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appDeleteFileOrDirectory( string path );

    public:
        MainProc( string cmdName );

        void processa( CMD* cmd, ProcManager* mgr );

};

#endif
