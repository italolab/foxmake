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
#include <thread>
#include <stdexcept>
#include <iostream>

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

void Shell::pushCommand( string command ) {
    commands.push_back( command );
}

Shell::Shell() {
    this->verboseFlag = true;
    this->showOutputFlag = true;
}

#ifdef _WIN32

typedef struct TThreadPipe {
    DWORD exitCode;
    std::thread* thread;
} ThreadPipe;

void runCMDThread( string command, ThreadPipe* tpipe, bool showOutputFlag ) {
    HANDLE hStdInRead;
    HANDLE hStdInWrite;
    HANDLE hStdOutRead;
    HANDLE hStdOutWrite;

    SECURITY_ATTRIBUTES secAttrs;
    secAttrs.nLength = sizeof( SECURITY_ATTRIBUTES );
    secAttrs.bInheritHandle = TRUE;
    secAttrs.lpSecurityDescriptor = NULL;

    WINBOOL result = CreatePipe( &hStdOutRead, &hStdOutWrite, &secAttrs, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao do pile de escrita." << endl;
        return;
    }
    
    result = SetHandleInformation( hStdOutRead, HANDLE_FLAG_INHERIT, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao das informacoes do handle de leitura." << endl;
        return;
    }

    result = CreatePipe( &hStdInRead, &hStdInWrite, &secAttrs, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
            cerr << "Erro na criacao do pile de leitura." << endl;
        return;
    }
    
    result = SetHandleInformation( hStdInWrite, HANDLE_FLAG_INHERIT, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao das informacoes do handle de escrita." << endl;
        return;
    }

    STARTUPINFO si;
    ZeroMemory( &si, sizeof(STARTUPINFO) );
    si.hStdError = hStdOutWrite;
    si.hStdOutput = hStdOutWrite;
    si.hStdInput = hStdInRead;
    si.dwFlags |= STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi;
    ZeroMemory( &pi, sizeof(PROCESS_INFORMATION) );

    result = CreateProcess( 
                NULL, 
                const_cast<char*>( command.c_str() ), 
                NULL, 
                NULL, 
                TRUE, 
                0, 
                NULL, 
                NULL, 
                &si, 
                &pi );

    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao do processo." << endl;
        return;
    }
        
    CloseHandle( hStdInRead );
    CloseHandle( hStdOutWrite );

    if ( showOutputFlag ) {
        const DWORD BUFFER_SIZE = 4096;
        char buffer[ BUFFER_SIZE ];
        DWORD bytesRead;

        bool isEnd = false;
        while( !isEnd ) {
            WINBOOL res = ReadFile( hStdOutRead, buffer, BUFFER_SIZE-1, &bytesRead, NULL );
            if ( !res || bytesRead == 0 ) {
                isEnd = true;
            } else {
                buffer[ bytesRead ] = '\0';
                cout << buffer;
            }
        }
    }

    WaitForSingleObject( pi.hProcess, INFINITE );

    GetExitCodeProcess( pi.hProcess, &(tpipe->exitCode) );

    CloseHandle( hStdOutRead );
    CloseHandle( hStdInWrite );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

int Shell::executa() {
    vector<ThreadPipe*> threadPipes;

    for( string command : commands ) {
        if ( verboseFlag )
            cout << command << endl;

        ThreadPipe* tpipe = new ThreadPipe;
        tpipe->thread = new std::thread( runCMDThread, command, tpipe, showOutputFlag );
        threadPipes.push_back( tpipe );
    }

    DWORD exitCode = 0;
    int len = threadPipes.size();
    for( int i = 0; i < len; i++ ) {
        threadPipes[ i ]->thread->join();

        if ( threadPipes[ i ]->exitCode != 0 )
            exitCode = threadPipes[ i ]->exitCode;
    }

    return exitCode;
}

#else

typedef struct TThreadPipe {
    FILE* pipe;
    std::thread* thread;
} ThreadPipe;

void runCMDThread( string command, ThreadPipe* threadPipe, bool showOutputFlag ) {
    FILE* pipe = popen( command.c_str(), "r" );
    if ( pipe ) {
        if ( showOutputFlag ) {
            char buffer[ 128 ];
            while( fgets( buffer, sizeof( buffer ), pipe ) != nullptr )
                cout << buffer;
        }
        threadPipe->pipe = pipe;
    } else {
        threadPipe->pipe = nullptr;
    }
}

int Shell::executa() {
    vector<ThreadPipe*> threadPipeVect;

    for( string command : commands ) {
        if ( verboseFlag )
            cout << command << endl;

        ThreadPipe* threadPipe = new ThreadPipe;
        threadPipe->thread = new std::thread( runCMDThread, command, threadPipe, showOutputFlag );
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

bool Shell::isVerbose() {
    return verboseFlag;
}

bool Shell::isShowOutput() {
    return showOutputFlag;
}

void Shell::setVerbose( bool flag ) {
    this->verboseFlag = flag;
}

void Shell::setShowOutput( bool flag ) {
    this->showOutputFlag = flag;
}
