#ifndef PROC_H
#define PROC_H

#include "../shell/CMD.h"
#include "../inter/MainInter.h"

#include <string>
#include <stdexcept>

using namespace std;

class proc_error : public runtime_error {

    public:
        proc_error( string msg );
};

class Proc {

    public:
        virtual void processa( CMD* cmd, MainInter* config ) = 0;

};

#endif
