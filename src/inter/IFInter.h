#ifndef IF_INTER_H
#define IF_INTER_H

#include "InterResult.h"
#include "condition/IFConditionInter.h"
#include "it/BlockIterator.h"
#include "../darv/Block.h"

class IFInter {
    
    private:
        IFConditionInter* ifConditionInter;

    public:
        IFInter();
        virtual ~IFInter();
        
        InterResult* interprets( 
                Block* parent, 
                BlockIterator* it, 
                string currentLine, 
                int& numberOfLineReaded, 
                bool isAddToParent,
                void* mgr );

};

#endif