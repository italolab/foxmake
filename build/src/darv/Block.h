#ifndef BLOCK_H
#define BLOCK_H

#include "No.h"
#include "Var.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Block : public No {

    private:
        map<string, Var*> varsMap;

    public:
        Block( Block* parent );

        void addVar( string name, string value );
        string getVarValue( string varName );
        bool existsVar( string varName );
        vector<string> vars();

};

#endif
