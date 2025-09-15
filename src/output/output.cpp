
#include "output.h"

#include <iostream>

using std::cout;

Output& Output::operator<<( string text ) {
    cout << text;
    return *this;
}

Output& Output::operator<<( std::ostream& (*stream)(std::ostream&) ) {
    cout << stream;
    return *this;
}

namespace output {

    string bold( string text ) {
        string output = "\033[1m";
        output += text;
        output += "\033[0m";
        return output;
    }
    
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

    string yellow( string text ) {
        string output = "\033[33m";
        output += text;
        output += "\033[0m";
        return output;
    }

}