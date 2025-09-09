#ifndef VAR_ATTR_H
#define VAR_ATTR_H

#include "Statement.h"
#include <string>

using std::string;

class VarAttr : public Statement {

    private:
        string name;
        string value;

    public:
        VarAttr( Statement* parent, string name, string value, int numberOfLinesReaded, string line );

        string getName();
        string getValue();
        void setValue( string value );

};

#endif
