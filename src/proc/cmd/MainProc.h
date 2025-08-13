#ifndef MAIN_PROC_H
#define MAIN_PROC_H

#include "Proc.h"
#include "../../darv/MainScript.h"

#include <string>

using namespace std;

class MainProc : public Proc {

    private:
        void procCMDs( void* mgr );
        void compileAndLink( CMD* cmd, void* manager, bool isCompile, bool isLink );

    public:
        void proc( CMD* cmd, void* mgr );

};

#endif
