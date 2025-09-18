
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

CMDThreadsController::CMDThreadsController( Shell* shell, OutputController* outputController ) {
    this->shell = shell;
    this->outputController = outputController;
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

void CMDThreadsController::run() {
    long numberOfCores = shell::getNumberOfProcessorCores();

    if ( numberOfCores == 0 )
        numberOfCores = 4;

    this->isWait = false;
    this->numberOfThreads = 0;

    vector<string>& commands = shell->getCommands();

    int threadNumber = 1;
    for( string command : commands ) {
        {
            std::unique_lock<std::mutex> lock( mtx );
            cv.wait( lock, [ this ] { return !this->isWait; } );
        }

        string cmdstr = command;
        size_t i = cmdstr.find( '\n' );
        if ( i != string::npos )
            cmdstr = cmdstr.substr( 0, i ) + "...";   

        stringstream ss;
        ss << "Thread #" << threadNumber;
        string threadName = ss.str();

        this->numberOfThreads++;

        OutputThread* outputThread = new OutputThread( this, threadName, cmdstr );

        ThreadPipe* tpipe = new ThreadPipe;
        tpipe->thread = new std::thread( runCMDThread, command, tpipe, outputThread );
        threadPipes.push_back( tpipe );

        outputController->addOutputThread( outputThread );

        threadNumber++;

        isWait = ( this->numberOfThreads >= numberOfCores-2 );
    }
}

void CMDThreadsController::commandProcessedNotify() {
    if ( numberOfThreads > 0 )
        numberOfThreads--;

    {
        std::lock_guard lock( mtx );
        this->isWait = false;
    }
    cv.notify_all();    
}

vector<ThreadPipe*>& CMDThreadsController::getThreadPipes() {
    return threadPipes;
}