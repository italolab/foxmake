#ifndef PROC_EXEC_H
#define PROC_EXEC_H

#include "ProcManager.h"
#include "Proc.h"
#include "MainProc.h"
#include "../darv/MainScript.h"
#include "../inter/MainScriptInterDriver.h"
#include "../inter/InterManager.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

class ProcExec : public ProcManager, MainScriptInterDriver {

    private:
        MainProc* mainProc;
        MainScript* mainScript;
        InterManager* interManager;
        map<string, map<string, Proc*>*> procsMapMap;
        string mainCMDName;

        map<string, Proc*>* getProcsMap( string cmdName );

    public:
        ProcExec();

        void exec( int argc, char* argv[] );

        vector<string> validSubCMDs( string cmdName );

        Proc* getProc( string cmdName, string subCmdName );
        MainProc* getMainProc();
        MainScript* getMainScript();
        InterManager* getInterManager();

        vector<string> validMainCMDNames();

};


#endif
