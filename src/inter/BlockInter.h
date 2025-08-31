#ifndef BLOCK_INTER_H
#define BLOCK_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "block/BlockInterResult.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"

class BlockInter : public Inter {

    protected:        
        BlockInterResult* interpretsBlock( 
                Block* block, 
                BlockIterator* it, 
                int lineNumber, 
                int& numberOfLines,  // Altera numberOfLines
                void* mgr );

        virtual InterResult* interpretsLine( 
                Block* block, 
                BlockIterator* it, 
                string currentLine, 
                int currentLineNumber,
                void* mgr ) = 0; 

        virtual InterResult* interpretsEnd( 
                Block* block,
                string currentLine, 
                int currentLineNumber ) = 0;

};

#endif