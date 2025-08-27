#include "exec/ExecManager.h"
#include "io/io.h"

#include <stdexcept>
#include <locale>

const string PT_BR_LOCALE = "pt_BR.UTF-8";
const string DEFAULT_LOCALE = "";

int main( int argc, char* argv[] ) {  
    try {
        std::locale testlocale( PT_BR_LOCALE );
        setlocale( LC_ALL, PT_BR_LOCALE.c_str() );
    } catch ( const std::runtime_error& ) {
        setlocale( LC_ALL, DEFAULT_LOCALE.c_str() );
    }
    
    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
