#ifndef PROP_INTER_H
#define PROP_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "../darv/MainScript.h"
#include "../darv/Block.h"

class PropInter : public Inter {

    public:
        InterResult* interprets( 
            MainScript* parent, string line, int& numberOfLinesReaded, void* mgr );

};

#endif
