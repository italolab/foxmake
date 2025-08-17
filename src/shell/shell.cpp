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

#include "shell.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <cstring>
#include <iostream>

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

Shell::Shell( bool isPrint ) {
    this->isPrint = isPrint;
}

void Shell::pushCommand( string command ) {
    commands.push_back( command );
}

#ifdef _WIN32
int Shell::executa() {
    STARTUPINFO si = { sizeof( si ) };

    vector<PROCESS_INFORMATION> vectPIs;

    for( string command : commands ) {
        if ( isPrint )
            cout << command << endl;

        PROCESS_INFORMATION pi;

        WINBOOL result = CreateProcess( NULL, const_cast<char*>( command.c_str() ), NULL, NULL, false, 0, NULL, NULL, &si, &pi );
        if ( result )
            vectPIs.push_back( pi );
    }

    for( PROCESS_INFORMATION pi : vectPIs )
        WaitForSingleObject( pi.hProcess, INFINITE );

    DWORD exitCode = 0;
    int len = vectPIs.size();
    for( int i = 0; exitCode == 0 && i < len; i++ ) {
        DWORD exitCode2;
        GetExitCodeProcess( vectPIs[ i ].hProcess, &exitCode2 );
        if ( exitCode2 != 0 )
            exitCode = exitCode2;
    }

    for( PROCESS_INFORMATION pi : vectPIs ) {
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }

    return exitCode;
}
#else
bool Shell::executa() {
    return false;
}
#endif
