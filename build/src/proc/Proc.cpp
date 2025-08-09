
#include "Proc.h"

proc_error::proc_error( string msg ) : runtime_error( msg ) {}

Proc::Proc( string cmdName ) {
    this->cmdName = cmdName;
}

string Proc::getCMDName() {
    return cmdName;
}

