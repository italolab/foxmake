
#include "Block.h"

Block::Block( Block* parent ) : No( parent ) {}

void Block::addVar( string name, string value ) {
    varsMap[ name ] = new Var( this, name, value );
}

bool Block::existsVar( string varName ) {
    return varsMap.find( varName ) != varsMap.end();
}

string Block::getVarValue( string varName ) {
    return varsMap[ varName ]->getValue();
}

vector<string> Block::vars() {
    vector<string> varsVect;
    for( const auto& pair : varsMap )
        varsVect.push_back( pair.first );
    return varsVect;
}
