#ifndef PROC_EXEC_H
#define PROC_EXEC_H

#include "ProcManager.h"
#include "cmd/Proc.h"
#include "cmd/MainProc.h"
#include "task/TaskProc.h"
#include "../darv/MainScript.h"
#include "../inter/BlockInterDriver.h"
#include "../inter/InterManager.h"

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

class ProcExec : public ProcManager, BlockInterDriver {

    private:
        MainProc* mainProc;
        MainScript* mainScript;
        InterManager* interManager;
        map<string, Proc*> procsMap;
        map<string, TaskProc*> taskProcsMap;
        vector<CPPFile*> cppFilesVect;

    public:
        ProcExec();

        void exec( int argc, char* argv[] );

        void reloadCPPFiles( string srcDir );

        vector<CPPFile*>& getCPPFiles();
        vector<string> validCMDNames();
        vector<string> registeredTaskProcNames();

        void executaCMDProc( CMD* cmd );

        bool isDefaultTask( string taskName );
        void executaTaskProc( string taskName, CMD* mainCMD );
        void executaTaskIfExists( string taskName );

        MainProc* getMainProc();
        MainScript* getMainScript();
        InterManager* getInterManager();

};


#endif
