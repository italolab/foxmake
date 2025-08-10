#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define __getcwd _getcwd
    #define __chdir _chdir
#else
    #include <unistd.h>
    #define __getcwd getcwd
    #define __chdir chdir
#endif

#include <cstring>
#include <iostream>

#include "shell.h"

using std::cout;
using std::cerr;
using std::endl;
using std::memset;

namespace shell {

    string getWorkingDir() {
        const int BUFSIZE = 4096;
        char buf[ BUFSIZE ];
        memset( buf, 0, BUFSIZE );
        __getcwd( buf, BUFSIZE-1 );
        string wdir( buf );
        return wdir;
    }

    bool setWorkingDir( string wdir ) {
        return __chdir( wdir.c_str() ) == 0;
    }

}

Shell::Shell( bool isPrintOutput ) {
    this->isPrintOutput = isPrintOutput;
}

void Shell::pushCommand( string command ) {
    commands.push_back( command );
}

#ifdef _WIN32
bool Shell::executa() {
    STARTUPINFO si = { sizeof( si ) };

    vector<PROCESS_INFORMATION> vectPIs;
    bool isError = false;

    for( string command : commands ) {
        PROCESS_INFORMATION pi;

        WINBOOL result = CreateProcess( NULL, const_cast<char*>( command.c_str() ), NULL, NULL, false, 0, NULL, NULL, &si, &pi );
        if ( result ) {
            vectPIs.push_back( pi );

            if ( isPrintOutput )
                cout << command << endl;
        } else {
            string msg = "cmd nao executado: " + command;

            if ( isPrintOutput )
                cerr << msg << endl;

            err << msg << endl;
            isError = true;
            break;
        }
    }

    for( PROCESS_INFORMATION pi : vectPIs ) {
        WaitForSingleObject( pi.hProcess, INFINITE );

        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }

    return !isError;
}
#else
bool Shell::executa() {
    return false;
}
#endif
