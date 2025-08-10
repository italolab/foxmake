#ifndef PROC_H
#define PROC_H

#include "../darv/CMD.h"

#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

class proc_error : public runtime_error {

    private:
        CMD* cmd;

    public:
        proc_error( CMD* cmd, string msg );

        string message() const;

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
