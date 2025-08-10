#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include "darv.h"
#include <string>

using std::string;

class AbstractBlock {

    public:
        virtual Variable* getLocalVar( string varName ) = 0;

};

#endif
