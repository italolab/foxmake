#ifndef BLOCK_INTER_H
#define BLOCK_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "block/BlockInterResult.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"

class BlockInter : public Inter {

    private:
        InterResult* interpretsEnd( 
                Block* block,
                string currentLine, 
                int& numberOfLinesReaded,
                string endToken );

    protected:        
        InterResult* interpretsBlock( 
                Block* block, 
                BlockIterator* it, 
                int& numberOfLinesReaded,
                string endToken,
                InterResult* endOfTokenNotFoundIR,
                void* mgr );

        virtual InterResult* interpretsLine( 
                Block* block, 
                BlockIterator* it, 
                string currentLine, 
                int& numberOfLinesReaded,
                void* mgr ) = 0; 

};

#endif