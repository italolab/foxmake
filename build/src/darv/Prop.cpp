
#include "Prop.h"

Prop::Prop( string name, string value ) : No( nullptr ) {
    this->name = name;
    this->value = value;
}

string Prop::getName() {
    return name;
}

string Prop::getValue() {
    return value;
}
