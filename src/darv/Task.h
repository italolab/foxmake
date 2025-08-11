#ifndef TASK_H
#define TASK_H

#include "Block.h"

#include <string>

using std::string;

class Task : public Block {

    private:
        string name;

    public:
        Task( Block* parent );

        string getName();
        void setName( string name );
};

#endif
