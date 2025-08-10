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
        map<string, Var*> localVarsMap;

    public:
        Block( Block* parent );

        void addLocalVar( string name, string value );
        Var* getLocalVar( string varName );
        bool existsLocalVar( string varName );
        vector<string> localVars();

        Var* getVar( string varName );

};

#endif
