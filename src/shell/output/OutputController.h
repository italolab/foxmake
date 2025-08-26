#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "OutputThread.h"

#include <vector>
#include <thread>
#include <mutex>

using std::vector;

class OutputController {

    private:
        vector<OutputThread*> outputThreadVect;

    public:
        void run();
        void finish();
        void addOutputThread( OutputThread* outputThread );

};

#endif