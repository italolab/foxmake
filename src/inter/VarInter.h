#ifndef VAR_INTER_H
#define VAR_INTER_H

#include "Inter.h"

#include <string>

using std::string;

class InterManager;

class VarInter : public Inter {

    public:
        InterResult* interpreta( Block* block, string line, int lineNumber, InterManager* manager );

};

#endif
