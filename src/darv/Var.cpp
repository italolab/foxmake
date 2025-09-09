
#include "Var.h"

Var::Var( string name, string value, int numberOfLinesReaded, string line ) {
    this->name = name;
    this->value = value;
    this->numberOfLinesReaded = numberOfLinesReaded;
    this->line = line;
}

string Var::getName() {
    return name;
}

string Var::getValue() {
    return value;
}

int Var::getNumberOfLinesReaded() {
    return numberOfLinesReaded;
}

void Var::setValue( string value ) {
    this->value = value;
}

