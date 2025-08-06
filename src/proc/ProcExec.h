#ifndef PROC_EXEC_H
#define PROC_EXEC_H

#include "ProcManager.h"
#include "Proc.h"
#include "MainProc.h"
#include "../inter/MainInter.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

class ProcExec : public ProcManager {

    private:
        MainProc* mainProc;
        MainInter* mainInter;
        map<string, map<string, Proc*>*> procsMapMap;

        map<string, Proc*>* getProcsMap( string cmdName );

    public:
        ProcExec();

        void exec( int argc, char* argv[] );

        vector<string> validSubCMDs( string cmdName );

        Proc* getProc( string cmdName, string subCmdName );
        MainProc* getMainProc();
        MainInter* getMainInter();


};


#endif
