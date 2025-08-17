
#include "Block.h"

Block::Block( Statement* parent, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {}

Block::~Block() {
    for( const auto& pair : localVarsMap )
        delete pair.second;
    for( Statement* st : statementsVect )
        delete st;
}

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
    if ( localVarsMap.find( varName ) != localVarsMap.end() )
        return localVarsMap[ varName ];
    return nullptr;
}

vector<string> Block::localVarNames() {
    vector<string> names;
    for( const auto& pair : localVarsMap )
        names.push_back( pair.first );
    return names;
}

void Block::addStatement( Statement* st ) {
    statementsVect.push_back( st );
}

int Block::getStatementsLength() {
    return statementsVect.size();
}

Statement* Block::getStatementByIndex( int i ) {
    return statementsVect[ i ];
}

vector<Statement*>& Block::statements() {
    return statementsVect;
}

