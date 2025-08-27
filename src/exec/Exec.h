#ifndef EXEC_H
#define EXEC_H

#include "../darv/CMD.h"
#include "../inter/InterResult.h"

class Exec {

    public:
        virtual ~Exec();

        virtual void exec( CMD* cmd, void* mgr ) = 0;

};

#endif
