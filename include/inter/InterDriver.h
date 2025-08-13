#ifndef INTER_DRIVER_H
#define INTER_DRIVER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class InterDriver {

    public:
        virtual vector<string> validCMDNames() = 0;
        virtual vector<string> validPropNames() = 0;
};

#endif
