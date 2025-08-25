
#include "OutputController.h"

#include <iostream>

using std::cout;
using std::endl;

OutputController::OutputController() {
    this->finishFlag = false;
}

void OutputController::run() {
    this->finishFlag = false;

    while( !finishFlag ) {
        if ( outputThreadQueue.empty() ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
            continue;
        }

        OutputThread* outputThread = outputThreadQueue.front();
        outputThreadQueue.pop();

        cout << outputThread->getName() << endl;

        while( !outputThread->isFinished() ) {
            if ( outputThread->hasNextOutput() ) {
                cout << outputThread->nextOutput();
            } else {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
            }
        }
    }
}

void OutputController::finish() {
    std::lock_guard<std::mutex> lock( mtx );
    finishFlag = true;    
}

void OutputController::addOutputThread( OutputThread* outputThread ) {
    outputThreadQueue.push( outputThread );
}