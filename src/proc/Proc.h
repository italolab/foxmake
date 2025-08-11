#ifndef PROC_H
#define PROC_H

#include "ProcManager.h"
#include "../darv/CMD.h"

#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

class proc_error : public runtime_error {

    private:
        CMD* cmd;
        int lineNumber;

    public:
        proc_error( CMD* cmd, string msg );
        proc_error( int lineNumber, string msg );

        string message() const;

};

class Proc {

    protected:
        string cmdName;

    public:
        Proc( string cmdName );

        virtual void processa( CMD* cmd, ProcManager* manager ) = 0;

        string getCMDName();

};

#endif
