
#include "CallCMD.h"

CallCMD::CallCMD( Block* parent, Proc* proc, int numberOfLinesReaded, string line  ) : CMD( parent, numberOfLinesReaded, line ) {
    this->proc = proc;
}

Proc* CallCMD::getProc() {
    return proc;
}


