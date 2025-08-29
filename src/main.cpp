#include "exec/ExecManager.h"
#include "io/io.h"

#include <test/cbtest.h>

#include <stdexcept>
#include <locale>

const string PT_BR_LOCALE = "pt_BR.UTF-8";
const string DEFAULT_LOCALE = "";

TEST_CASE( teste1, ) {
    ASSERT_EQUALS( 1, 1, );
}

int main( int argc, char* argv[] ) {  
    try {
        std::locale testlocale( PT_BR_LOCALE );
        setlocale( LC_ALL, PT_BR_LOCALE.c_str() );
    } catch ( const std::runtime_error& ) {
        setlocale( LC_ALL, DEFAULT_LOCALE.c_str() );
    }

    if ( argc > 1 ) {
        if ( strcmp( argv[ 1 ], "test" ) == 0 ) {
            ADD_TEST_CASE( teste1, );
            RUN_TEST_CASES_MENU();
            return 0;
        }
    }
    
    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
