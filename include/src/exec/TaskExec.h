#ifndef TASK_EXEC_H
#define TASK_EXEC_H

#include "Proc.h"
#include "../shell/CMD.h"
#include "../inter/MainInter.h"

#include <map>
#include <string>

using namespace std;

class TaskExec {

    private:
        map<string, Proc*> procsMap;

        void procCMDs( MainInter* inter );

        void clean( CMD* cmd, MainInter* inter );
        void compileAndLink( CMD* cmd, MainInter* inter, bool isCompile, bool isLink );
        void copyFiles( CMD* cmd, MainInter* inter );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appDeleteFileOrDirectory( string path );
        vector<string> validCMDs();


    public:
        TaskExec();

        void proc( int argc, char* argv[] );

};

#endif
