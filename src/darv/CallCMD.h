#ifndef CALL_CMD_H
#define CALL_CMD_H

#include "CMD.h"
#include "Proc.h"

class CallCMD : public CMD {

    private:
        Proc* proc;

    public:
        CallCMD( Block* parent, Proc* proc, int numberOfLinesReaded, string line  );

        Proc* getProc();
};

#endif