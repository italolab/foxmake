
#include "Proc.h"
#include "CMD.h"
#include "Task.h"

#include <queue>
#include <vector>
#include <map>

using std::queue;
using std::vector;
using std::map;

Proc::Proc( Statement* parent, string name, int numberOfLinesReaded, string line ) : Block( parent, numberOfLinesReaded, line ) {
    this->name = name;
}

Proc* Proc::newProc( Statement* newParent ) {
    int numberOfLinesReaded = Statement::getNumberOfLinesReaded();
    string line = Statement::getLine();

    vector<Statement*> statementsVect = Block::getStatements();
    map<string, Var*> localVarsMap = Block::getLocalVarsMap();

    Proc* proc = new Proc( newParent, name, numberOfLinesReaded, line );
    proc->load( localVarsMap, statementsVect );
    return proc;
}

string Proc::getName() {
    return name;
}

void Proc::setName( string name ) {
    this->name = name;
}