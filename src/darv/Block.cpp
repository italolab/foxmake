
#include "Block.h"

Block::Block( Statement* parent, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {}

Statement* Block::getRoot() {
    if ( Statement::getParent() == nullptr )
        return this;
    return ((Block*)Statement::getParent())->getRoot();
}

Var* Block::getVar( string varName ) {
    Var* var = this->getLocalVar( varName );
    if ( var != nullptr )
        return var;

    Block* parent = (Block*)Statement::getParent();
    if ( parent != nullptr )
        return parent->getVar( varName );

    return nullptr;
}

void Block::putLocalVar( string name, string value ) {
    localVarsMap[ name ] = new Var( this, name, value, 0, "" );
}

void Block::putLocalVar( Var* var ) {
    localVarsMap[ var->getName() ] = var;
}

bool Block::existsLocalVar( string varName ) {
    return localVarsMap.find( varName ) != localVarsMap.end();
}

Var* Block::getLocalVar( string varName ) {
    return localVarsMap[ varName ];
}

vector<string> Block::localVarNames() {
    vector<string> names;
    for( const auto& pair : localVarsMap )
        names.push_back( pair.first );
    return names;
}

void Block::addCMD( CMD* cmd ) {
    cmdsVect.push_back( cmd );
}

int Block::getCMDsLength() {
    return cmdsVect.size();
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

vector<CMD*>& Block::cmds() {
    return cmdsVect;
}
