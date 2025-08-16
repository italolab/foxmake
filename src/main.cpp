#include "exec/ExecManager.h"
#include "io/io.h"

int main( int argc, char* argv[] ) {
    ExecManager* executor = new ExecManager();
    executor->executor( argc, argv );

    delete executor;

    return 0;
}
