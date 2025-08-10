
#include "Block.h"

Block::Block( Block* parent ) : No( parent ) {}

Var* Block::getVar( string varName ) {
    Var* var = this->getLocalVar( varName );

    Block* parent = No::getParent();
    if ( var == nullptr && parent != nullptr )
        return parent->getVar( varName );

    return nullptr;
}

void Block::addLocalVar( string name, string value ) {
    localVarsMap[ name ] = new Var( this, name, value );
}

bool Block::existsLocalVar( string varName ) {
    return localVarsMap.find( varName ) != localVarsMap.end();
}

Var* Block::getLocalVar( string varName ) {
    return localVarsMap[ varName ];
}

vector<string> Block::localVars() {
    vector<string> varsVect;
    for( const auto& pair : localVarsMap )
        varsVect.push_back( pair.first );
    return varsVect;
}
