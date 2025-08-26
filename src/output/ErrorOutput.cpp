
#include "ErrorOutput.h"

#include <iostream>

using std::cerr;

Output& ErrorOutput::operator<<( string text ) {
    cerr << "\033[31m" << text << "\033[0m";
    return *this;
}