#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "Inter.h"
#include "BlockInterDriver.h"
#include "it/BlockIterator.h"
#include "../darv/MainScript.h"

class MainScriptInter : public Inter {

    private:
        BlockInterDriver* drv;

    public:
        MainScriptInter( BlockInterDriver* drv );

        InterResult* interprets( MainScript* script, string file, int lineNumber, void* mgr );

};

#endif
