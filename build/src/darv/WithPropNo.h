#ifndef WITH_PROP_NO_H
#define WITH_PROP_NO_H

#include <string>

using std::string;

class WithPropNo {

    public:
        virtual bool existsProperty( string name ) = 0;
        virtual string getPropertyValue( string name ) = 0;

};

#endif
