
#include "BlockInter.h"

BlockInter::BlockInter( BlockInter* blockInter ) : Inter( blockInter ) {}

void BlockInter::addVar( string name, string value ) {
    varsMap[ name ] = value;
}

bool BlockInter::existsVar( string varName ) {
    return varsMap.find( varName ) != varsMap.end();
}

string BlockInter::getVarValue( string varName ) {
    return varsMap[ varName ];
}

vector<string> BlockInter::vars() {
    vector<string> varsVect;
    for( const auto& pair : varsMap )
        varsVect.push_back( pair.first );
    return varsVect;
}
