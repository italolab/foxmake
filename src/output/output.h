#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <iostream>

using std::string;

namespace output {
    
    string bold( string text );

    string yellow( string text );
    string red( string text );
    string green( string text );
    string blue( string text );
    string white( string text );

}

class Output {

    public:
        Output& operator<<( string text );
        Output& operator<<( std::ostream& (*stream)(std::ostream&) );

};

#endif