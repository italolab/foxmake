#ifndef VAR_ATTR_INTER_H
#define VAR_ATTR_INTER_H

#include "InterResult.h"
#include "../darv/Block.h"

class VarAttrInter {

    public:
        InterResult* interprets( 
            Block* parent, string line, int& numberOfLinesReaded, void* mgr );

};

#endif