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

    public:
        ProcExec();

        void exec( int argc, char* argv[] );

        Proc* getProc( string cmdName );
        MainProc* getMainProc();
        MainScript* getMainScript();
        InterManager* getInterManager();

        vector<string> validCMDNames();

};


#endif
