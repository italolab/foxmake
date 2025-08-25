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
#include "output/OutputController.h"
#include "output/OutputThread.h"
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

Shell::Shell() {
    this->verboseFlag = true;
    this->showOutputFlag = true;
}

#ifdef _WIN32

void runCMDThread( string command, ThreadPipe* tpipe, OutputThread* outputThread, bool showOutputFlag ) {
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
        tpipe->exitCode = -1;
        return;
    }
    
    result = SetHandleInformation( hStdOutRead, HANDLE_FLAG_INHERIT, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao das informacoes do handle de leitura." << endl;
        tpipe->exitCode = -1;
        return;
    }

    result = CreatePipe( &hStdInRead, &hStdInWrite, &secAttrs, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao do pile de leitura." << endl;
        tpipe->exitCode = -1;
        return;
    }
    
    result = SetHandleInformation( hStdInWrite, HANDLE_FLAG_INHERIT, 0 );
    if ( !result ) {
        cerr << "Nao foi possivel executar o(s) comando(s) no shell." << endl;
        cerr << "Erro na criacao das informacoes do handle de escrita." << endl;
        tpipe->exitCode = -1;
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
        tpipe->exitCode = -1;
        return;
    }
        
    CloseHandle( hStdInRead );
    CloseHandle( hStdOutWrite );

    if ( showOutputFlag ) {
        outputThread->run( hStdOutRead );
    } else {
        outputThread->doNotRun();
    }

    WaitForSingleObject( pi.hProcess, INFINITE );

    GetExitCodeProcess( pi.hProcess, &(tpipe->exitCode) );

    CloseHandle( hStdOutRead );
    CloseHandle( hStdInWrite );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

#else

void runCMDThread( string command, ThreadPipe* threadPipe, OutputThread* outputThread, bool showOutputFlag ) {
    FILE* pipe = popen( command.c_str(), "r" );
    if ( pipe ) {
        if ( showOutputFlag ) {
            outputThread->run( hStdOutRead );
        } else {
            outputThread->doNotRun();
        }
        
        threadPile->exitCode = pclose( pipe );
    } else {
        threadPipe->exitCode = -1;
    }
}

#endif

void runOutputControllerThread( OutputController* outputController ) {
    outputController->run();
}

int Shell::executa() {
    vector<ThreadPipe*> threadPipes;
    OutputController* outputController = new OutputController();

    int threadNumber = 1;
    for( string command : commands ) {
        if ( verboseFlag ) {
            string cmdstr = command;
            size_t i = cmdstr.find( '\n' );
            if ( i != string::npos )
                cmdstr = cmdstr.substr( 0, i ) + "...";
                
            cout << cmdstr << endl;
        }

        stringstream ss;
        ss << "Thread #" << threadNumber;

        OutputThread* outputThread = new OutputThread( ss.str() );

        ThreadPipe* tpipe = new ThreadPipe;
        tpipe->thread = new std::thread( runCMDThread, command, tpipe, outputThread, showOutputFlag );
        threadPipes.push_back( tpipe );

        outputController->addOutputThread( outputThread );

        threadNumber++;
    }

    std::thread outputControllerThread( runOutputControllerThread, outputController );

    DWORD exitCode = 0;
    int len = threadPipes.size();
    for( int i = 0; i < len; i++ ) {
        threadPipes[ i ]->thread->join();

        if ( threadPipes[ i ]->exitCode != 0 )
            exitCode = threadPipes[ i ]->exitCode;
    }

    outputControllerThread.join();

    return exitCode;
}

void Shell::pushCommand( string command ) {
    commands.push_back( command );
}

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
