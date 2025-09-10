#ifndef PROPS_AND_VARS_REPLACER_H
#define PROPS_AND_VARS_REPLACER_H

#include "InterResult.h"
#include "../darv/Block.h"

#include <string>

using std::string;

class PropsAndVarsReplacer {

    public:
        InterResult* replacePropsAndVarsAndDollarSigns( 
                    string& text, 
                    int& numberOfLinesReaded, 
                    string line, 
                    Block* block );

};

#endif