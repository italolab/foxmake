#include "exec/ExecManager.h"
#include "io/io.h"

int main( int argc, char* argv[] ) {
    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
