
#include "VarAttr.h"

VarAttr::VarAttr( Statement* parent, string name, string value, int numberOfLinesReaded, string line ) : Statement( parent, numberOfLinesReaded, line ) {
    this->name = name;
    this->value = value;
}

string VarAttr::getName() {
    return name;
}

string VarAttr::getValue() {
    return value;
}

void VarAttr::setValue( string value ) {
    this->value = value;
}
