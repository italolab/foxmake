#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "OutputThread.h"

#include <queue>
#include <thread>
#include <mutex>

using std::queue;

class OutputController {

    private:
        queue<OutputThread*> outputThreadQueue;
        bool finishFlag;
        std::mutex mtx;

    public:
        OutputController();

        void run();
        void finish();
        void addOutputThread( OutputThread* outputThread );

};

#endif