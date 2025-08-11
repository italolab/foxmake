#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "BlockInter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"

class MainScriptInter : public BlockInter {

    private:
        MainScript* script;

    protected:
        InterResult* extInterpretsLine( Block* script, BlockIterator* it, string currentLine, int lineNumber, void* manager );

        BlockIterator* createBlockIterator( string str );
        string errorMSGForNotRecognizedStatement();
        Block* getBlock();

    public:
        MainScriptInter( BlockInterDriver* drv );

        InterResult* interprets( MainScript* script, string file, int lineNumber, void* mgr );

};

#endif
