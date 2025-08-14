#include "proc/ProcExec.h"
#include "io/io.h"

#include <iostream>
using namespace std;

int main( int argc, char* argv[] ) {
    ProcExec* exec = new ProcExec();
    exec->exec( argc, argv );
    return 0;
}
