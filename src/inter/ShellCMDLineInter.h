#ifndef SHELL_CMD_LINE_INTER_H
#define SHELL_CMD_LINE_INTER_H

#include "InterResult.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"

#include <string>

using std::string;

class ShellCMDLineInter {

    public:
        InterResult* interprets( 
            Block* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

};

#endif

