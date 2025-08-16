#ifndef PROC_MANAGER_H
#define PROC_MANAGER_H

#include "Exec.h"
#include "TaskExec.h"
#include "main/MainExec.h"
#include "shcmd/ShellCMDExec.h"
#include "../darv/Statement.h"
#include "../darv/MainScript.h"
#include "../inter/InterManager.h"
#include "../inter/InterDriver.h"
#include "../io/SourceCodeManager.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class ExecManager : public InterDriver {

    private:
        MainScript* mainScript;

        InterManager* interManager;
        SourceCodeManager* sourceCodeManager;

        MainExec* mainExec;
        ShellCMDExec* shellCMDExec;

        map<string, Exec*> execsMap;
        map<string, TaskExec*> taskExecsMap;

    public:
        ExecManager();
        virtual ~ExecManager();

        void executor( int argc, char* argv[] );

        void executaStatement( Statement* st );

        bool isDefaultTask( string taskName );
        void executaTask( string taskName, CMD* mainCMD );
        void executaTaskIfExists( string taskName );

        vector<string> validCMDNames();

        MainExec* getMainExec();
        MainScript* getMainScript();
        InterManager* getInterManager();
        SourceCodeManager* getSourceCodeManager();

        vector<string> validPropNames();
        vector<string> registeredTaskProcNames();

};


#endif
