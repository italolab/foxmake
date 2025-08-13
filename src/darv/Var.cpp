
#include "Var.h"

Var::Var( Statement* parent, string name, string value, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
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
