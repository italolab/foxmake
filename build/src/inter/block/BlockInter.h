#ifndef BLOCK_INTER_H
#define BLOCK_INTER_H

#include "it/BlockIterator.h"
#include "../Inter.h"
#include "../InterResult.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class BlockInter : public Inter {

    private:
        map<string, string> varsMap;

    public:
        BlockInter( BlockInter* blockInter );

        virtual InterResult* interpreta( BlockIterator* blockIt, int lineNumber ) = 0;

        void addVar( string name, string value );
        string getVarValue( string varName );
        bool existsVar( string varName );
        vector<string> vars();

};

#endif
