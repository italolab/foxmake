#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "OutputThread.h"
#include "../../output/Output.h"

#include <vector>
#include <thread>
#include <mutex>

using std::vector;

class OutputController {

    private:
        vector<OutputThread*> outputThreadVect;
        bool showOutputFlag;

        Output* out;
        Output* inf;

    public:
        OutputController( Output* out, Output* inf, bool showOutputFlag );
        void run();
        void finish();
        void addOutputThread( OutputThread* outputThread );

};

#endif