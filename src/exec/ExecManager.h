#ifndef EXEC_MANAGER_H
#define EXEC_MANAGER_H

#include "Exec.h"
#include "TaskExec.h"
#include "ArgManager.h"
#include "main/MainExec.h"
#include "shcmd/ShellCMDExec.h"
#include "../darv/Statement.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"
#include "../darv/CMD.h"
#include "../inter/InterManager.h"
#include "../inter/InterDriver.h"
#include "../io/SourceCodeManager.h"
#include "../output/TextOutput.h"
#include "../output/InfoOutput.h"
#include "../output/ErrorOutput.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class ExecManager : public InterDriver {

    private:
        MainScript* mainScript;
        CMD* mainCMD;

        InterManager* interManager;
        SourceCodeManager* sourceCodeManager;
        ArgManager* argManager;

        MainExec* mainExec;
        ShellCMDExec* shellCMDExec;

        map<string, Exec*> execsMap;
        map<string, TaskExec*> taskExecsMap;

    public:
        TextOutput out;
        InfoOutput inf;
        ErrorOutput err;

        ExecManager();

        virtual ~ExecManager();

        void exec( int argc, char* argv[] );

        void executaStatement( Statement* st );

        bool isDefaultTask( string taskName );
        void executaTask( string taskName );
        void executaUserTaskIfExists( string taskName, TaskExecution taskExecution );

        vector<string> validCMDNames();
        vector<string> validPropNames();
        vector<string> validDefaultTaskNames();

        MainExec* getMainExec();
        MainScript* getMainScript();
        CMD* getMainCMD();
        InterManager* getInterManager();
        SourceCodeManager* getSourceCodeManager();
        ArgManager* getArgManager();

};


#endif
