#include "proc/ProcExec.h"
#include "io/io.h"

int main( int argc, char* argv[] ) {
    ProcExec* exec = new ProcExec();
    exec->exec( argc, argv );

    delete exec;

    return 0;
}
