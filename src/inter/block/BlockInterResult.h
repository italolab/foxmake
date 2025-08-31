#ifndef BLOCK_INTER_RESULT_H
#define BLOCK_INTER_RESULT_H

#include "../InterResult.h"

class BlockInterResult {

    private:
        InterResult* interResult;
        bool endFound;

    public:
        BlockInterResult( InterResult* interResult, bool endFound );

        InterResult* getInterResult();
        bool isEndFound();

};

#endif