#ifndef PROP_INTER_H
#define PROP_INTER_H

#include "InterResult.h"
#include "../darv/MainScript.h"
#include "../darv/Block.h"

class PropInter {

    public:
        InterResult* interprets( 
            MainScript* parent, string line, int& numberOfLinesReaded, void* mgr );

};

#endif
