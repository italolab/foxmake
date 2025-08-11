#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "BlockInter.h"
#include "it/BlockIterator.h"

class MainScriptInter : public BlockInter {

    public:
        MainScriptInter( BlockInterDriver* drv );

        InterResult* interpretsLine( Block* block, string line, int lineNumber, AbstractInterManager* manager );
        BlockIterator* createBlockIterator( string str );
        Block* createBlock( Block* block );
        string errorMSGForNotRecognizedStatement();

        InterResult* interprets( string str, int lineNumber, AbstractInterManager* mgr );

};

#endif
