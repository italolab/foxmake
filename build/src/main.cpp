#include "proc/ProcExec.h"

int main( int argc, char* argv[] ) {
    ProcExec* exec = new ProcExec();
    exec->exec( argc, argv );
    return 0;
}
