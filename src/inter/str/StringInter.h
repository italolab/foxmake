#ifndef LINE_INTER_H
#define LINE_INTER_H

#include "../InterResult.h"

#include <string>

using std::string;

class StringInter {

    public:
        InterResult* interpreta( string line, int lineNumber );

};

#endif
