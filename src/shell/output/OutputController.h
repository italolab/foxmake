#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "OutputThread.h"

#include <queue>

using std::queue;

class OutputController {

    private:
        queue<OutputThread*> outputThreadQueue;
        
    public:
        void run();
        void addOutputThread( OutputThread* outputThread );

};

#endif