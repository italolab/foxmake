#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "BlockInter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"

class MainScriptInter : public BlockInter {

    private:
        MainScript* script;

    public:
        MainScriptInter( BlockInterDriver* drv );

        InterResult* interpretsLine( Block* script, string line, int lineNumber, void* manager );
        BlockIterator* createBlockIterator( string str );
        Block* createOrGetBlock( Block* parent );
        string errorMSGForNotRecognizedStatement();

        InterResult* interprets( MainScript* script, string str, int lineNumber, void* mgr );

};

#endif
