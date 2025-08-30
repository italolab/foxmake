#ifndef COMPILE_TASK_EXEC_H
#define COMPILE_TASK_EXEC_H

#include "../TaskExec.h"
#include "../../../io/CodeInfo.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class CompileTaskExec : public TaskExec {

    private:
        void loadFilesToCompile( 
                vector<CodeInfo*>& filesToCompile, 
                vector<string>& incDirs,
                void* mgr );
        
        void appCreateDirs( string dir, void* mgr );

    public:
        void exec( void* mgr );

};

#endif
