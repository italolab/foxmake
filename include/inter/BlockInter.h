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
        virtual InterResult* interpretsLine( Block* block, string line, int lineNumber, void* mgr ) = 0;
        virtual BlockIterator* createBlockIterator( string str ) = 0;
        virtual Block* createOrGetBlock( Block* parent ) = 0;
        virtual string errorMSGForNotRecognizedStatement() = 0;

    public:
        BlockInter( BlockInterDriver* drv );

        InterResult* interprets2( Block* parent, string str, int lineNumber, void* mgr );
};

#endif
