
#include "TextOutput.h"

#include <iostream>

using std::cout;

Output& TextOutput::operator<<( string text ) {
    cout << text;
    return *this;
}