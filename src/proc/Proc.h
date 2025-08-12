#ifndef PROC_H
#define PROC_H

#include "ProcManager.h"
#include "../darv/CMD.h"
#include "../inter/InterResult.h"

#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

class proc_error : public runtime_error {

    private:
        int lineNumber;
        string line;

    public:
        proc_error( CMD* cmd, string msg );
        proc_error( InterResult* result );

        string message() const;

};

class Proc {

    public:
        virtual void processa( CMD* cmd, ProcManager* manager ) = 0;

};

#endif
