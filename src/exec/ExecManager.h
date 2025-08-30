#ifndef EXEC_MANAGER_H
#define EXEC_MANAGER_H

#include "Exec.h"
#include "MainCMDArgManager.h"
#include "main/MainExec.h"
#include "shcmd/ShellCMDExec.h"
#include "../darv/Statement.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"
#include "../darv/CMD.h"
#include "../inter/InterManager.h"
#include "../inter/InterDriver.h"
#include "../io/SourceCodeManager.h"
#include "../output/output.h"

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
        SourceCodeManager* testSourceCodeManager;
        MainCMDArgManager* mainCMDArgManager;

        MainExec* mainExec;
        ShellCMDExec* shellCMDExec;

        map<string, Exec*> execsMap;

    public:
        Output out;

        ExecManager();

        virtual ~ExecManager();

        void exec( int argc, char* argv[] );

        void executaStatement( Statement* st );

        bool isDefaultTask( string taskName );
        bool isValidProp( string propName ); 
        bool isValidCMD( string propName );

        void executaUserTaskIfExists( string taskName, TaskExecution taskExecution );

        MainExec* getMainExec();
        MainScript* getMainScript();
        CMD* getMainCMD();
        InterManager* getInterManager();
        SourceCodeManager* getSourceCodeManager();
        SourceCodeManager* getTestSourceCodeManager();
        MainCMDArgManager* getMainCMDArgManager();

};

#endif
