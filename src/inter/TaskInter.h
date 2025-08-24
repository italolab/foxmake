#ifndef GOAL_INTER_H
#define GOAL_INTER_H

#include "Inter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"

#include <vector>

using std::vector;

class TaskInter : public Inter {

    private:
        vector<string> VALID_FLAGS = {
            "before", 
            "after", 
            "verbose", 
            "noverbose", 
            "showoutput", 
            "noshowoutput" 
        };
    
        void setFlags( Task* task, vector<string>& flags );
        bool isBeforeFlag( vector<string>& flags );

    public:
        InterResult* interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr );

};

#endif
