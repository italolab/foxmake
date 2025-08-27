#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;

namespace output {

    string red( string text );
    string green( string text );
    string blue( string text );
    string white( string text );

}

class Output {

    public:
        Output& operator<<( string text );

};

#endif