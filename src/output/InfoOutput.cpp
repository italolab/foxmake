#include "InfoOutput.h"

#include <iostream>

using std::cout;

Output& InfoOutput::operator<<( string text ) {
    cout << "\033[32m" << text << "\033[0m";
    return *this;
}