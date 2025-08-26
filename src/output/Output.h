#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

using std::string;

class Output {

    public:
        virtual Output& operator<<( string text ) = 0;

};

#endif