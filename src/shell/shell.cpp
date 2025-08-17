#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define __getcwd _getcwd
    #define __chdir _chdir
#else
    #include <thread>
    #include <unistd.h>
    #define __getcwd getcwd
    #define __chdir chdir
#endif

#include "shell.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;
using std::memset;
using std::runtime_error;

namespace shell {

    string getWorkingDir() {
        char buffer[ 4096 ];
        memset( buffer, 0, sizeof( buffer ) );
        char* result = __getcwd( buffer, sizeof( buffer ) );
        if ( result != nullptr ) {
            string wdir( buffer );
            return wdir;
        }
        throw runtime_error( errors::CURRENT_DIRECTORY_NOT_GET );
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

typedef struct TThreadPipe {
    FILE* pipe;
    std::thread* thread;
} ThreadPipe;

void runCMDThread( string command, ThreadPipe* threadPipe ) {
    FILE* pipe = popen( command.c_str(), "r" );
    if ( pipe ) {
        char buffer[ 128 ];
        while( fgets( buffer, sizeof( buffer ), pipe ) != nullptr )
            cout << buffer;

        threadPipe->pipe = pipe;
    } else {
        threadPipe->pipe = nullptr;
    }

}

int Shell::executa() {
    vector<ThreadPipe*> threadPipeVect;

    for( string command : commands ) {
        if ( isPrint )
            cout << command << endl;

        ThreadPipe* threadPipe = new ThreadPipe;
        threadPipe->thread = new std::thread( runCMDThread, command, threadPipe );
        threadPipeVect.push_back( threadPipe );
    }

    for( ThreadPipe* tp : threadPipeVect )
        tp->thread->join();

    int resultCode = 0;
    for( ThreadPipe* tp : threadPipeVect ) {
        if ( tp->pipe == nullptr )
            resultCode = -1;            
        else {
            int code = pclose( tp->pipe );
            if ( resultCode == 0 )
                resultCode = code;
        }
    }

    return resultCode;
}

#endif
