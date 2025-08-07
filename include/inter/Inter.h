#ifndef INTER_H
#define INTER_H

#include <string>
#include <stdexcept>

using namespace std;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

class Inter {

    public:
        string replaceVars( string line, int lineNumber );

        virtual string getPropertyValue( string name ) = 0;

};

#endif
