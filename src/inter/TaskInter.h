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
        void setFlags( Task* task, vector<string>& flags );
        bool isBeforeFlag( vector<string>& flags );
        bool isValidFlag( string flag );

    public:
        InterResult* interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr );

};

#endif
