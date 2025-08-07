#ifndef PROC_H
#define PROC_H

#include "../cmd/CMD.h"

#include <string>
#include <stdexcept>

using namespace std;

class proc_error : public runtime_error {

    public:
        proc_error( string msg );
};

class ProcManager;

class Proc {

    protected:
        string cmdName;

    public:
        Proc( string cmdName );

        virtual void processa( CMD* cmd, ProcManager* mgr ) = 0;

        string getCMDName();

};

#endif
