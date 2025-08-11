#ifndef GOAL_H
#define GOAL_H

#include "Block.h"

#include <string>

using std::string;

class Goal : public Block {

    private:
        string name;

    public:
        Goal( Block* parent );

        string getName();
        void setName( string name );
};

#endif
