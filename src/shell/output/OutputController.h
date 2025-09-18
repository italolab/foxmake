#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "OutputThread.h"
#include "../shell.h"
#include "../../output/output.h"

#include <vector>
#include <thread>
#include <mutex>

using std::vector;

class OutputController {

    private:
        vector<OutputThread*> outputThreadVect;
        
        Shell* shell;
        bool isFinish;

        std::mutex mtx;

    public:
        OutputController( Shell* shell );
        void run();
        void finish();
        void addOutputThread( OutputThread* outputThread );

};

#endif