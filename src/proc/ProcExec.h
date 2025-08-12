#ifndef PROC_EXEC_H
#define PROC_EXEC_H

#include "ProcManager.h"
#include "Proc.h"
#include "MainProc.h"
#include "../darv/MainScript.h"
#include "../inter/BlockInterDriver.h"
#include "../inter/InterManager.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

class ProcExec : public ProcManager, BlockInterDriver {

    private:
        MainProc* mainProc;
        MainScript* mainScript;
        InterManager* interManager;
        map<string, Proc*> procsMap;
        map<string, Proc*> taskProcsMap;
        vector<CPPFile*> cppFilesVect;

    public:
        ProcExec();

        void exec( int argc, char* argv[] );

        Proc* getProc( string cmdName );
        Proc* getTaskProc( string taskName );

        void reloadCPPFiles( string srcDir );

        vector<CPPFile*>& getCPPFiles();
        vector<string> validCMDNames();
        vector<string> registeredTaskProcNames();

        bool isDefaultTask( string taskName );
        void executaTaskProc( string taskName, CMD* mainCMD );
        void executaTaskIfExists( string taskName );

        MainProc* getMainProc();
        MainScript* getMainScript();
        InterManager* getInterManager();

};


#endif
