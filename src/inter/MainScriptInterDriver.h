#ifndef MAIN_INTER_DRIVER_H
#define MAIN_INTER_DRIVER_H

#include <string>
#include <vector>

using namespace std;

class MainScriptInterDriver {

    public:
        virtual vector<string> validMainCMDNames() = 0;

};

#endif
