#ifndef NO_IN_BLOCK_VAR_ATTR_INTER_H
#define NO_IN_BLOCK_VAR_ATTR_INTER_H

#include "InterResult.h"
#include "../darv/Block.h"

#include <string>

using std::string;

class NoInBlockVarAttrInter {

    public:
        InterResult* interprets( 
            Block* parent, string line, int& numberOfLinesReaded, void* mgr );

};

#endif
