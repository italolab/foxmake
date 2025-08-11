
#include "Goal.h"

Goal::Goal( Block* parent ) : Block( parent ) {}

string Goal::getName() {
    return name;
}

void Goal::setName( string name ) {
    this->name = name;
}
