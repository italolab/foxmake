#ifndef BLOCK_H
#define BLOCK_H

#include "Statement.h"
#include "Var.h"
#include "CMD.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Block : public Statement {

    private:
        map<string, Var*> localVarsMap;
        vector<CMD*> cmdsVect;

    public:
        Block( Statement* parent, int lineNumber );

        Statement* getRoot();

        void addCMD( CMD* cmd );
        int getCMDsLength();
        CMD* getCMDByIndex( int i );
        vector<CMD*>& cmds();

        void putLocalVar( string name, string value );
        void putLocalVar( Var* var );
        Var* getLocalVar( string varName );
        bool existsLocalVar( string varName );
        vector<string> localVarNames();

        Var* getVar( string varName );

};

#endif
