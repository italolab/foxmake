#ifndef GOAL_INTER_H
#define GOAL_INTER_H

#include "BlockInter.h"
#include "BlockInterDriver.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"
#include "../darv/MainScript.h"
#include "../darv/Goal.h"

class GoalInter : public BlockInter {

    private:
        Goal* goal;

    protected:
        InterResult* extInterpretsLine( Block* script, BlockIterator* it, string currentLine, int lineNumber, void* manager );

        BlockIterator* createBlockIterator( string str );
        string errorMSGForNotRecognizedStatement();
        Block* getBlock();

    public:
        GoalInter( BlockInterDriver* drv );

        InterResult* interprets( Block* goal, BlockIterator* it, string currentLine, int lineNumber, void* mgr );

};

#endif
