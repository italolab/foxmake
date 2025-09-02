#ifndef PROC_H
#define PROC_H

#include "Block.h"

#include <string>

using std::string;

class Proc : public Block {

    private:
        string name;
    
    public:
        Proc( Statement* parent, string name, int numberOfLinesReaded, string line );

        string getName();
        void setName( string name );

};

#endif
