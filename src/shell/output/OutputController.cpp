
#include "OutputController.h"

#include <iostream>

using std::cout;

void OutputController::run() {
    while( !outputThreadQueue.empty() ) {
        OutputThread* outputThread = outputThreadQueue.front();
        outputThreadQueue.pop();
        while( !outputThread->isFinished() ) {
            if ( outputThread->hasNextOutput() ) {
                cout << outputThread->nextOutput();
            } else {
                std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
            }
        }
    }
}

void OutputController::addOutputThread( OutputThread* outputThread ) {
    outputThreadQueue.push( outputThread );
}