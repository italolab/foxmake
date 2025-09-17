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
#include "CMDThreadsController.h"
#include "output/OutputController.h"
#include "output/OutputThread.h"
#include "../msg/messagebuilder.h"

#include "../error_messages.h"

#include <cstring>
#include <thread>
#include <stdexcept>
#include <iostream>

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

    long getNumberOfProcessorCores() {
        #ifdef _WIN32
            SYSTEM_INFO sysinfo;
            GetSystemInfo( &sysinfo );
            return sysinfo.dwNumberOfProcessors;
        #else
            return sysconf( _SC_NPROCESSORS_ONLN );
        #endif
    }

}

/*
A classe Shell gerencia um lote de comandos de shell iniciados em processos 
concorrentemente
*/

Shell::Shell( Output& out ) {
    this->out = &out;
    this->verboseFlag = true;
    this->showOutputFlag = true;
}

void runOutputControllerThread( OutputController* outputController ) {
    outputController->run();
}

void runThreadsControllerThread( CMDThreadsController* threadsController ) {
    threadsController->run();
}

int Shell::execute() {
    OutputController* outputController = new OutputController( this );
    CMDThreadsController* cmdThreadsController = new CMDThreadsController( this, outputController );

    std::thread cmdThreadsControllerThread( runThreadsControllerThread, cmdThreadsController );
    std::thread outputControllerThread( runOutputControllerThread, outputController );

    vector<ThreadPipe*>& threadPipes = cmdThreadsController->getThreadPipes();

    cmdThreadsControllerThread.join();
    
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

vector<string>& Shell::getCommands() {
    return commands;
}

Output* Shell::getOutput() {
    return out;
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
