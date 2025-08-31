#ifndef VAR_H
#define VAR_H

#include "Statement.h"
#include <string>

using std::string;

class Var : public Statement {

    private:
        string name;
        string value;

    public:
        Var( Statement* parent, string name, string value, int numberOfLinesReaded, string line );

        string getName();
        string getValue();
        void setValue( string value );

};

#endif
