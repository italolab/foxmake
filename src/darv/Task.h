#ifndef TASK_H
#define TASK_H

#include "Block.h"

#include <string>

using std::string;

class Task : public Block {

    private:
        string name;

    public:
        Task( Statement* parent, int lineNumber, string line );

        string getName();
        void setName( string name );
};

#endif
