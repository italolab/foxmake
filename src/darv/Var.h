#ifndef VAR_H
#define VAR_H

#include "No.h"
#include <string>

using std::string;

class Block;

class Var : public No {

    private:
        string name;
        string value;

    public:
        Var( Block* parent, string name, string value );

        string getName();
        string getValue();
        void setValue( string value );

};

#endif
