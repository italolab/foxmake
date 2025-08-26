
#include "OutputController.h"

#include <iostream>

using std::cout;

void OutputController::run() {
    for( OutputThread* outputThread : outputThreadVect ) { 
        while( !outputThread->isFinished() || outputThread->hasNextOutput() ) {
            if ( outputThread->hasNextOutput() ) {
                cout << outputThread->nextOutput();
            } else {
                std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
            }
        }
    }
}

void OutputController::finish() {
    for( OutputThread* outputThread : outputThreadVect )        
        outputThread->finish();    
}

void OutputController::addOutputThread( OutputThread* outputThread ) {
    outputThreadVect.push_back( outputThread );
}