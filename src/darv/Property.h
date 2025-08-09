#ifndef PROPERTY_H
#define PROPERTY_H

#include "No.h"

#include <string>

using std::string;

class Property : public No {

    private:
        string name;
        string value;

    public:
        Property( Block* parent, string name, string value );

        string getName();
        string getValue();

};

#endif // PROPERTY_H
