#ifndef PRE_PROC_SCRIPT_H
#define PRE_PROC_SCRIPT_H

#include "../it/BlockIterator.h"
#include "../InterResult.h"
#include "../if/IFConditionInter.h"
#include "../../darv/Block.h"

class PreProcessor {

    private:
        IFConditionInter* ifConditionInter;

    public:
        PreProcessor();
        virtual ~PreProcessor();

        InterResult* preProcess( 
                    Block* block, 
                    BlockIterator* it, 
                    string& preProcessedBlock, 
                    void* mgr );

};

#endif