#ifndef TASK_MGR_H
#define TASK_MGR_H

#include "Args.h"
#include "ArgsInter.h"
#include "Properties.h"
#include "util.h"

class TaskExec {

    private:
        void clean( Args* args, Properties* props );
        void compileAndLink( Args* args, Properties* props, bool isCompile, bool isLink );

        void ordersCPPFilesByDependencies( vector<CPPFile*>& cppFiles, vector<string>& cppFilesInOrder );
        void ordersCPPFilesDependencies( vector<CPPFile*>& cppFiles, vector<string>& cppFilesInOrder, string cppFile );

    public:
        void proc( int argc, char* argv[] );

};

#endif
