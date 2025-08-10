
#include "Property.h"

Property::Property( string name, string value ) : No( nullptr ) {
    this->name = name;
    this->value = value;
}

string Property::getName() {
    return name;
}

string Property::getValue() {
    return value;
}
