#ifndef PROC_INTER_H
#define PROC_INTER_H

#include "BlockInter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"
#include "../darv/Task.h"

#include <vector>

using std::vector;

class ProcInter : public BlockInter {

    private:
        InterResult* endTokenNotFoundIResult;

        InterResult* interpretsLine( 
            Block* block, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

        string getEndToken();
        InterResult* getEndTokenNotFoundInterResult();

    public:
        virtual ~ProcInter();

        InterResult* interprets( 
            MainScript* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

};

#endif