#ifndef PROC_H
#define PROC_H

#include "Block.h"

#include <string>

using std::string;

class Proc : public Block {

    private:
        string name;
    
    public:
        const string CALL_CMD_NAME = "call";

        Proc( Statement* parent, string name, int numberOfLinesReaded, string line );

        Proc* newProc( Statement* newParent );
        
        string getName();
        void setName( string name );

};

#endif
