#ifndef STRING_INTER_RESULT_H
#define STRING_INTER_RESULT_H

#include "../InterResult.h"

class StringInterResult : public InterResult {

    public:
        StringInterResult( string errorMsg );
        StringInterResult( int numberOfColumns );

};

#endif
