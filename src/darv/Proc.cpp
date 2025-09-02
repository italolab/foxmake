
#include "Proc.h"

Proc::Proc( Statement* parent, string name, int numberOfLinesReaded, string line ) : Block( parent, numberOfLinesReaded, line ) {
    this->name = name;
}

string Proc::getName() {
    return name;
}

void Proc::setName( string name ) {
    this->name = name;
}