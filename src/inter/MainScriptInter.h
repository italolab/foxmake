#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "Inter.h"
#include "BlockInter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"

class MainScriptInter : public BlockInter {

    private:
        InterResult* interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );
        
    public:
        virtual ~MainScriptInter();
        InterResult* interprets( 
            MainScript* script, string file, void* mgr );

};

#endif
