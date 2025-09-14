#ifndef PRE_PROC_SCRIPT_H
#define PRE_PROC_SCRIPT_H

#include "it/BlockIterator.h"
#include "InterResult.h"
#include "condition/IFConditionInter.h"
#include "../darv/Block.h"

class IFPreProcessor {

    private:
        IFConditionInter* ifConditionInter;

    public:
        IFPreProcessor();
        virtual ~IFPreProcessor();

        InterResult* preProcess( 
                    Block* block, 
                    BlockIterator* it, 
                    string& preProcessedBlock, 
                    void* mgr );

};

#endif