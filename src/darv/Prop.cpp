
#include "Prop.h"

Prop::Prop( string name, string value, int numberOfLinesReaded, string line ) {
    this->name = name;
    this->value = value;
    this->numberOfLinesReaded = numberOfLinesReaded;
    this->line = line;
}

string Prop::getName() {
    return name;
}

string Prop::getValue() {
    return value;
}

int Prop::getNumberOfLinesReaded() {
    return numberOfLinesReaded;
}

string Prop::getLine() {
    return line;
}
