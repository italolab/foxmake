#ifndef EXEC_MANAGER_H
#define EXEC_MANAGER_H

#include "MainCMDArgManager.h"
#include "main/MainExec.h"
#include "cp/CPExec.h"
#include "rm/RMExec.h"
#include "cd/CDExec.h"
#include "mkdir/MKDirExec.h"
#include "echo/EchoExec.h"
#include "shcmd/ShellCMDLineExec.h"
#include "../darv/Statement.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"
#include "../darv/CMD.h"
#include "../inter/InterManager.h"
#include "../inter/InterDriver.h"
#include "../sourcecode/SourceCodeManager.h"
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
        CPExec* cpExec;
        RMExec* rmExec;
        CDExec* cdExec;
        MKDirExec* mkdirExec;
        EchoExec* echoExec;

        ShellCMDLineExec* shellCMDExec;

        vector<string> validCMDNames;

    public:
        Output out;

        ExecManager();

        virtual ~ExecManager();

        void exec( int argc, char* argv[] );

        void executeBlockStatements( Block* block );
        void executeStatement( Statement* st );

        bool isDefaultTask( string taskName );
        bool isValidProp( string propName ); 
        bool isValidCMD( string propName );

        void executeUserTaskIfExists( string taskName, TaskExecution taskExecution );
        bool executeProc( string procName );

        MainExec* getMainExec();
        MainScript* getMainScript();
        CMD* getMainCMD();
        InterManager* getInterManager();
        SourceCodeManager* getSourceCodeManager();
        SourceCodeManager* getTestSourceCodeManager();
        MainCMDArgManager* getMainCMDArgManager();

};

#endif
