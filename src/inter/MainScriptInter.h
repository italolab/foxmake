#ifndef MAIN_SCRIPT_INTER_H
#define MAIN_SCRIPT_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "MainScriptInterDriver.h"

class MainScriptInter : public Inter {

    private:
        MainScriptInterDriver* drv;

    public:
        MainScriptInter( MainScriptInterDriver* drv );

        InterResult* interpreta( string file, int lineNumber, InterManager* manager );

        InterResult* interpreta( Block* block, string file, int lineNumber, InterManager* manager );

};

#endif
