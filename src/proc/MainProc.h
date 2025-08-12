#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "Proc.h"
#include "ProcManager.h"
#include "../darv/MainScript.h"
#include "../darv/CMD.h"

#include <string>

using namespace std;

class MainProc : public Proc {

    private:
        void procCMDs( ProcManager* mgr );
        void compileAndLink( CMD* cmd, ProcManager* manager, bool isCompile, bool isLink );

    public:
        void processa( CMD* cmd, ProcManager* mgr );

};

#endif
