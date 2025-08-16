#ifndef PROC_EXEC_H
#define PROC_EXEC_H

#include "ProcManager.h"
#include "Proc.h"
#include "TaskProc.h"
#include "main/MainProc.h"
#include "shcmd/ShellCMDProc.h"
#include "../darv/MainScript.h"
#include "../inter/InterDriver.h"
#include "../inter/InterManager.h"
#include "../io/SourceCodeManager.h"

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

class ProcExec : public ProcManager, InterDriver {

    private:
        MainProc* mainProc;
        MainScript* mainScript;
        InterManager* interManager;
        map<string, Proc*> procsMap;
        map<string, TaskProc*> taskProcsMap;
        ShellCMDProc* shellCMDProc;
        SourceCodeManager* sourceCodeManager;

    public:
        ProcExec();
        virtual ~ProcExec();

        void exec( int argc, char* argv[] );

        vector<string> validCMDNames();
        vector<string> validPropNames();
        vector<string> registeredTaskProcNames();

        void executaStatement( Statement* st );

        bool isDefaultTask( string taskName );
        void executaTaskProc( string taskName, CMD* mainCMD );
        void executaTaskIfExists( string taskName );

        MainProc* getMainProc();
        MainScript* getMainScript();
        SourceCodeManager* getSourceCodeManager();
        InterManager* getInterManager();

};


#endif
