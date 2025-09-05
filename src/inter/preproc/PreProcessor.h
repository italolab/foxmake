#ifndef PRE_PROC_SCRIPT_H
#define PRE_PROC_SCRIPT_H

#include "../it/BlockIterator.h"
#include "../InterResult.h"

class PreProcessor {

    public:
        InterResult* preProcess( BlockIterator* it, string& preProcessedBlock );

};

#endif