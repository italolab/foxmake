#ifndef BLOCK_H
#define BLOCK_H

#include "No.h"
#include "Var.h"
#include "CMD.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Block : public No {

    private:
        map<string, Var*> localVarsMap;
        vector<CMD*> cmdsVect;

    public:
        Block( Block* parent );

        Block* getRoot();

        void addCMD( CMD* cmd );
        CMD* getCMD( string name );
        int getCMDsLength();
        CMD* getCMDByIndex( int i );
        vector<CMD*> cmds();

        void addLocalVar( string name, string value );
        void addLocalVar( Var* var );
        Var* getLocalVar( string varName );
        bool existsLocalVar( string varName );
        vector<string> localVars();

        Var* getVar( string varName );

};

#endif
