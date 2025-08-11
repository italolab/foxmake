#ifndef INTER_H
#define INTER_H

#include <string>
#include <stdexcept>

#include "InterResult.h"
#include "../darv/Block.h"

using std::string;
using std::runtime_error;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

class Inter {

    public:
        InterResult* replacePropsAndVars( string& line, int lineNumber, Block* block );

};

#endif
