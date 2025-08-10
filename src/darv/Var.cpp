
#include "Var.h"

Var::Var( Block* parent, string name, string value ) : No( parent ) {
    this->name = name;
    this->value = value;
}

string Var::getName() {
    return name;
}

string Var::getValue() {
    return value;
}

void Var::setValue( string value ) {
    this->value = value;
}
