#ifndef BLOCK_INTER_DRIVER_H
#define BLOCK_INTER_DRIVER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class BlockInterDriver {

    public:
        virtual vector<string> validMainCMDNames() = 0;

};

#endif
