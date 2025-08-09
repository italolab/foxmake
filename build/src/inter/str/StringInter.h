#ifndef LINE_INTER_H
#define LINE_INTER_H

#include "StringInterResult.h"
#include "../Inter.h"


#include <string>

using std::string;

class StringInter : public Inter {

    public:
        StringInter( BlockInter* blockInter );

        StringInterResult* interpreta( string line, int lineNumber );


};

#endif
