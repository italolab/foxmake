#ifndef BLOCK_INTER_H
#define BLOCK_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "BlockInterDriver.h"
#include "it/BlockIterator.h"

#include <string>

using std::string;

class BlockInter : public Inter {

    private:
        BlockInterDriver* drv;

    protected:
        virtual InterResult* extInterpretsLine( Block* block, BlockIterator* it, string currentLine, int lineNumber, void* mgr ) = 0;
        virtual BlockIterator* createBlockIterator( string str ) = 0;
        virtual string errorMSGForNotRecognizedStatement() = 0;
        virtual Block* getBlock() = 0;

    public:
        BlockInter( BlockInterDriver* drv );

        InterResult* interpretsBlock( Block* parent, string blockStr, int lineNumber, void* mgr );
};

#endif
