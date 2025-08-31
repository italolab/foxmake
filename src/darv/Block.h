#ifndef BLOCK_H
#define BLOCK_H

#include "Statement.h"
#include "Var.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Block : public Statement {

    private:
        map<string, Var*> localVarsMap;
        vector<Statement*> statementsVect;

    public:
        Block( Statement* parent, int numberOfLinesReaded, string line );
        virtual ~Block();

        void addStatement( Statement* cmd );
        int getStatementsLength();
        Statement* getStatementByIndex( int i );
        vector<Statement*>& statements();

        void putLocalVar( string name, string value );
        void putLocalVar( Var* var );
        Var* getLocalVar( string varName );
        bool existsLocalVar( string varName );
        vector<string> localVarNames();

        Var* getVar( string varName );

};

#endif
