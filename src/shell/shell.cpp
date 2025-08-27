#ifdef _WIN32
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

typedef struct TThreadPipe {
    int exitCode;
    std::thread* thread;
} ThreadPipe;

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

Shell::Shell( Output& out ) {
    this->out = &out;
    this->verboseFlag = true;
    this->showOutputFlag = true;
}

void runCMDThread( string command, ThreadPipe* threadPipe, OutputThread* outputThread ) {
    FILE* pipe = popen( command.c_str(), "r" );
    if ( pipe ) {
        outputThread->run( pipe );
                
        threadPipe->exitCode = pclose( pipe );
    } else {
        threadPipe->exitCode = -1;
    }
}

void runOutputControllerThread( OutputController* outputController ) {
    outputController->run();
}

int Shell::executa() {
    vector<ThreadPipe*> threadPipes;
    OutputController* outputController = new OutputController( out, showOutputFlag );

    int threadNumber = 1;
    for( string command : commands ) {
        if ( verboseFlag ) {
            string cmdstr = command;
            size_t i = cmdstr.find( '\n' );
            if ( i != string::npos )
                cmdstr = cmdstr.substr( 0, i ) + "...";
                
            *out << cmdstr << "\n";
        }

        stringstream ss;
        ss << "Thread #" << threadNumber;

        OutputThread* outputThread = new OutputThread( ss.str() );

        ThreadPipe* tpipe = new ThreadPipe;
        tpipe->thread = new std::thread( runCMDThread, command, tpipe, outputThread );
        threadPipes.push_back( tpipe );

        outputController->addOutputThread( outputThread );

        threadNumber++;
    }

    std::thread outputControllerThread( runOutputControllerThread, outputController );

    int exitCode = 0;
    int len = threadPipes.size();
    for( int i = 0; i < len; i++ ) {
        threadPipes[ i ]->thread->join();

        if ( threadPipes[ i ]->exitCode != 0 )
            exitCode = threadPipes[ i ]->exitCode;
    }

    outputController->finish();
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
