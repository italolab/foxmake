#ifndef GENERIC_CMD_H
#define GENERIC_CMD_H

#include "Statement.h"

class GenericCMD : public Statement {

    public:
        GenericCMD( Statement* parent, int numberOfLinesReaded, string line );
        virtual Statement* getTask() = 0;

};

#endif