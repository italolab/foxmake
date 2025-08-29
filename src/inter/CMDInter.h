#ifndef CMD_INTER_H
#define CMD_INTER_H

#include "Inter.h"

#include <string>

class InterManager;

class CMDInter : public Inter{

    private:
        InterResult* interprets( Block* parent, int argc, char* argv[], int lineNumber, void* mgr );

    public:
        InterResult* interprets( Block* parent, string line, int lineNumber, void* mgr );
        InterResult* interpretsMainCMD( int argc, char* argv[], void* mgr );

};

#endif
