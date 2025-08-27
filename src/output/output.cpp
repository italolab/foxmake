
#include "output.h"

#include <iostream>

using std::cout;

Output& Output::operator<<( string text ) {
    cout << text;
    return *this;
}

namespace output {
    
    string red( string text ) {
        string output = "\033[31m";
        output += text;
        output += "\033[0m";
        return output;
    }

    string green( string text ) {
        string output = "\033[32m";
        output += text;
        output += "\033[0m";
        return output;
    }

    string blue( string text ) {
        string output = "\033[34m";
        output += text;
        output += "\033[0m";
        return output;
    }

    string white( string text ) {
        string output = "\033[37m";
        output += text;
        output += "\033[0m";
        return output;
    }

}