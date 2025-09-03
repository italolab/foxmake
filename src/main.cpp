#ifdef __WIN32
    #include <windows.h>
#endif

#include "exec/ExecManager.h"

#include <locale>
#include <string>
#include <cstring>

#include <iostream>

using namespace std;

#ifdef _WIN32
    const string PT_BR_LOCALE = "C";
#else
    const string PT_BR_LOCALE = "pt_BR.UTF-8";
#endif

const string DEFAULT_LOCALE = "";

int main( int argc, char* argv[] ) {  
    char* defaultLocale = setlocale( LC_ALL, nullptr );
    
    std::setlocale( LC_ALL, PT_BR_LOCALE.c_str() );
    if ( strcmp( setlocale( LC_ALL, nullptr ), "C" ) == 0 )
        std::setlocale( LC_ALL, defaultLocale );        
      
    #ifdef _WIN32
        SetConsoleOutputCP( CP_UTF8 );
    #endif

    ExecManager* manager = new ExecManager();
    manager->exec( argc, argv );

    delete manager;

    return 0;
}
