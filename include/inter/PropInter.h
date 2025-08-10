#ifndef PROP_INTER_H
#define PROP_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "../darv/Block.h"

class InterManager;

class PropInter : public Inter {

    public:
        InterResult* interpreta( WithPropNo* no, string str, int lineNumber, InterManager* manager );

};

#endif
