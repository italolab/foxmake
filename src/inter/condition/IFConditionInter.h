#ifndef IF_CONDITION_INTER_H
#define IF_CONDITION_INTER_H

#include "../InterResult.h"
#include "../../darv/Block.h"

#include <string>

using std::string;

class IFConditionInter {

    public:
        InterResult* interprets( 
            Block* parent,
            string condition,
            string& value1, 
            string& value2, 
            string& compOperator,
            string line, 
            int numberOfLinesReaded, 
            void* mgr );

};

#endif