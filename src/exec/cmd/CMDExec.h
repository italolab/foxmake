#ifndef CMD_EXEC_H
#define CMD_EXEC_H

#include "../../darv/CMD.h"
#include "cp/CPExec.h"
#include "rm/RMExec.h"
#include "cd/CDExec.h"
#include "mkdir/MKDirExec.h"
#include "echo/EchoExec.h"

#include <string>

using std::string;

class CMDExec {

    private:
        CPExec* cpExec;
        RMExec* rmExec;
        CDExec* cdExec;
        MKDirExec* mkdirExec;
        EchoExec* echoExec;

    public:
        CMDExec();
        virtual ~CMDExec();

        void exec( CMD* cmd, void* mgr );

};

#endif
