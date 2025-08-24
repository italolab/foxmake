#include "exec/ExecManager.h"
#include "io/io.h"

#include <iostream>
using namespace std;

int main( int argc, char* argv[] ) {    
    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
