#ifndef IF_EXEC_H
#define IF_EXEC_H

#include "../../darv/IF.h"

#include <string>

using std::string;

class IFExec {

    public:
        void exec( IF* ifst, void* mgr );

};

#endif
