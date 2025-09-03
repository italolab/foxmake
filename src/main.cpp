#include "exec/ExecManager.h"

#include <stdexcept>
#include <locale>

#ifdef _WIN32
    const string PT_BR_LOCALE = "Portuguese_Brazil.1252";
#else
    const string PT_BR_LOCALE = "pt_BR.UTF-8";
#endif

const string DEFAULT_LOCALE = "";

bool setLocale( string locale ) {
    try {
        std::locale testlocale( PT_BR_LOCALE );
        setlocale( LC_ALL, locale.c_str() );
        return true;
    } catch ( const std::runtime_error& ) {
        return false;
    }
}

int main( int argc, char* argv[] ) {  
    try {
        std::locale testlocale( PT_BR_LOCALE );
        setlocale( LC_ALL, PT_BR_LOCALE.c_str() );
        return true;
    } catch ( const std::runtime_error& ) {
        setlocale( LC_ALL, DEFAULT_LOCALE.c_str() );
    }
            
    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
