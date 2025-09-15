#ifndef EXEC_MANAGER_H
#define EXEC_MANAGER_H

#include "MainCMDArgManager.h"
#include "ScriptPropertyManager.h"
#include "main/MainExec.h"
#include "cmd/CMDExec.h"
#include "shcmd/ShellCMDLineExec.h"
#include "if/IFExec.h"
#include "varattr/VarAttrExec.h"
#include "call/CallExec.h"
#include "cmd/ExecCMD.h"
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

        InterManager* interManager;
        SourceCodeManager* sourceCodeManager;
        SourceCodeManager* testSourceCodeManager;
        MainCMDArgManager* mainCMDArgManager;
        ScriptPropertyManager* scriptPropertyManager;

        MainExec* mainExec;
        ExecCMD* mainExecCMD;

        ShellCMDLineExec* shellCMDExec;
        CMDExec* cmdExec;
        IFExec* ifExec;
        VarAttrExec* varAttrExec;
        CallExec* callExec;

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
        ExecCMD* getMainExecCMD();
        
        InterManager* getInterManager();
        SourceCodeManager* getSourceCodeManager();
        SourceCodeManager* getTestSourceCodeManager();

        MainCMDArgManager* getMainCMDArgManager();
        ScriptPropertyManager* getScriptPropManager();

};

#endif
