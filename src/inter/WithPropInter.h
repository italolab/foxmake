#ifndef WITH_PROP_INTER_H
#define WITH_PROP_INTER_H

#include <string>

using std::string;

class WithPropInter {

    public:
        virtual bool existsProperty( string name ) = 0;
        virtual string getPropertyValue( string name ) = 0;

};

#endif
