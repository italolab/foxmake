#ifndef IF_INTER_H
#define IF_INTER_H

#include "Inter.h"
#include "InterResult.h"
#include "it/BlockIterator.h"

#include "../darv/Block.h"

class IFInter : public Inter {
    
    private:
        InterResult* interpretsCondition( 
            Block* parent,
            string condition,
            string& value1, 
            string& value2, 
            string& compOperator,
            string line, 
            int numberOfLinesReaded );

        bool loadVarOrPropertyValueOfOperand( 
            Block* parent, 
            string operand, 
            string& value, 
            string& errorMsg );

    public:
        InterResult* interprets( 
                Block* parent, 
                BlockIterator* it, 
                string currentLine, 
                int& numberOfLineReaded, 
                bool isAddToParent,
                void* mgr );

};

#endif