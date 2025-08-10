#ifndef PROP_H
#define PROP_H

#include "No.h"

#include <string>

using std::string;

class Prop : public No {

    private:
        string name;
        string value;

    public:
        Prop( string name, string value );

        string getName();
        string getValue();

};

#endif
