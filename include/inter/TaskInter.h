#ifndef GOAL_INTER_H
#define GOAL_INTER_H

#include "Inter.h"
#include "BlockInterDriver.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"

class TaskInter : public Inter {

    private:
        BlockInterDriver* drv;

    public:
        TaskInter( BlockInterDriver* drv );

        InterResult* interprets( MainScript* parent, BlockIterator* it, string currentLine, int lineNumber, void* mgr );

};

#endif
