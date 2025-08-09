#ifndef CMD_INTER_H
#define CMD_INTER_H

#include "Inter.h"

#include <string>

class CMDInter : public Inter {

    private:
        InterResult* interpreta( Block* block, int argc, char* argv[], int lineNumber, InterManager* manager );

    public:
        InterResult* interpreta( Block* block, string cmdstr, int lineNumber, InterManager* manager );
        InterResult* interpretaMainCMD( int argc, char* argv[], InterManager* manager );


};

#endif
