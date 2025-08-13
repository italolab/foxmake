#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "Inter.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"

class MainScriptInter : public Inter {

    public:
        InterResult* interprets( MainScript* script, string file, int lineNumber, void* mgr );

};

#endif
