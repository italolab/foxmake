
#include "Prop.h"

Prop::Prop( Statement* parent, string name, string value, int numberOfLinesReaded, string line ) : Statement( parent, numberOfLinesReaded, line ) {
    this->name = name;
    this->value = value;
}

string Prop::getName() {
    return name;
}

string Prop::getValue() {
    return value;
}
