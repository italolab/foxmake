#include "exec/TaskExec.h"

int main( int argc, char* argv[] ) {
    TaskExec* exec = new TaskExec();
    exec->proc( argc, argv );
    return 0;
}
