#ifndef TASK_EXEC_H
#define TASK_EXEC_H

#include "Proc.h"
#include "../shell/CMD.h"
#include "../config/Config.h"

#include <map>
#include <string>

using namespace std;

class TaskExec {

    private:
        map<string, string> validCMDs;

        void procCMDs( Config* config );

        void clean( CMD* cmd, Config* config );
        void compileAndLink( CMD* cmd, Config* config, bool isCompile, bool isLink );
        void copyFiles( CMD* cmd, Config* config );

        void appCopyFileOrDirectoryToBuild( string path, string buildDir );
        void appDeleteFileOrDirectory( string path );
        vector<string> validCMDsKeys();


    public:
        TaskExec();

        void proc( int argc, char* argv[] );

};

#endif
