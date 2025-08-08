#ifndef BLOCK_INTER_H
#define BLOCK_INTER_H

#include "it/BlockIterator.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class BlockInter {

    private:
        map<string, string> varsMap;

    public:
        virtual void interpreta( BlockIterator* blockIt ) = 0;

        void addVar( string name, string value );
        string getVarValue( string varName );
        bool existsVar( string varName );
        vector<string> vars();

};

#endif
