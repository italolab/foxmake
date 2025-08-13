#ifndef PROP_H
#define PROP_H

#include "Statement.h"

#include <string>

using std::string;

class Prop : public Statement {

    private:
        string name;
        string value;

    public:
        Prop( Statement* block, string name, string value, int lineNumber, string line );

        string getName();
        string getValue();

};

#endif
