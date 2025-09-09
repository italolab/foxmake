#ifndef CONCRETE_BLOCK_INTER_H
#define CONCRETE_BLOCK_INTER_H

#include "BlockInter.h"
#include "InterResult.h"
#include "block/BlockInterResult.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"

class ConcreteBlockInter : public BlockInter {

    private:
        InterResult* interpretsLine( 
                Block* block, 
                BlockIterator* it, 
                string currentLine, 
                int& numberOfLinesReaded,
                void* mgr );

    public:
        virtual ~ConcreteBlockInter();
        
        InterResult* interprets( 
                Block* block, 
                BlockIterator* it, 
                int& numberOfLinesReaded,
                void* mgr );

};

#endif