
#include "Block.h"

Block::Block( Block* parent ) : No( parent ) {}

Block* Block::getRoot() {
    if ( No::getParent() == nullptr )
        return this;
    return No::getParent()->getRoot();
}

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

void Block::addLocalVar( Var* var ) {
    localVarsMap[ var->getName() ] = var;
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

void Block::addCMD( CMD* cmd ) {
    cmdsVect.push_back( cmd );
}

int Block::getCMDsLength() {
    return cmdsVect.size();
}

CMD* Block::getCMD( string name ) {
    for( CMD* cmd : cmdsVect )
        if ( cmd->getName() == name )
            return cmd;
    return nullptr;
}

CMD* Block::getCMDByIndex( int i ) {
    int k = 0;
    for( CMD* cmd : cmdsVect ) {
        if ( k == i )
            return cmd;
        k++;
    }
    return nullptr;
}

vector<CMD*> Block::cmds() {
    return cmdsVect;
}
