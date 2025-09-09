#ifndef CALL_EXEC_H
#define CALL_EXEC_H

#include "../../darv/CallCMD.h"

#include <string>

using std::string;

class CallExec {

    public:
        void exec( CallCMD* callCMD, void* mgr );

};

#endif
