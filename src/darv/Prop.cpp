
#include "Prop.h"

Prop::Prop( Statement* parent, string name, string value, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
    this->name = name;
    this->value = value;
}

string Prop::getName() {
    return name;
}

string Prop::getValue() {
    return value;
}
