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
        vector<string> defaultTasks{ "clean", "compile", "link", "build", "copy" };

        void procCMDs( ProcManager* mgr );

        void clean( CMD* cmd, MainScript* script, ProcManager* manager );
        void compileAndLink( CMD* cmd, MainScript* script, ProcManager* manager, bool isCompile, bool isLink );
        void copyFiles( CMD* cmd, MainScript* script, ProcManager* manager );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appRecursiveDeleteFileOrDirectoryIfExists( string path );

        void executaTaskIfExists( string goalName, ProcManager* manager );
        bool isDefaultTask( string TaskName );

    public:
        void processa( CMD* cmd, ProcManager* mgr );

};

#endif
