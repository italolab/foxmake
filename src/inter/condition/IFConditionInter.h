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
            bool& value1PropOrVar,
            bool& value2PropOrVar,
            string line, 
            int numberOfLinesReaded, 
            void* mgr );

};

#endif