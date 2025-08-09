
#include "Property.h"

Property::Property( Block* parent, string name, string value ) : No( parent ) {
    this->name = name;
    this->value = value;
}

string Property::getName() {
    return name;
}

string Property::getValue() {
    return value;
}
