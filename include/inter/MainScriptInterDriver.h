#ifndef MAIN_SCRIPT_INTER_DRIVER_H
#define MAIN_SCRIPT_INTER_DRIVER_H

#include "BlockInterDriver.h"

class MainScriptInterDriver : public BlockInterDriver {

    public:
        virtual vector<string> validPropNames() = 0;

};

#endif
