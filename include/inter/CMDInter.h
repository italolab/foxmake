#ifndef CMD_INTER_H
#define CMD_INTER_H

#include "Inter.h"

#include <string>

class InterManager;

class CMDInter : public Inter {

    private:
        InterResult* interprets( Block* parent, int argc, char* argv[], int lineNumber, InterManager* manager );

    public:
        InterResult* interprets( Block* parent, string line, int lineNumber, InterManager* manager );
        InterResult* interpretsMainCMD( int argc, char* argv[], InterManager* manager );

        bool isValidCMD( string line, vector<string>& validCMDss );

};

#endif
