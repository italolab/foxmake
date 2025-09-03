#ifndef SHELL_CMD_LINE_INTER_H
#define SHELL_CMD_LINE_INTER_H

#include "Inter.h"
#include "it/BlockIterator.h"

#include <string>

using std::string;

class ShellCMDLineInter : public Inter {

    public:
        InterResult* interprets( 
            Block* parent, 
            BlockIterator* it, 
            string currentLine, 
            int& numberOfLinesReaded, 
            void* mgr );

};

#endif

