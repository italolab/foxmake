#ifndef VAR_INTER_H
#define VAR_INTER_H

#include "StringInter.h"

#include <string>

using std::string;

class VarInter : public StringInter {

    private:
        string name;
        string value;

    public:
        StringInterResult* interpreta( string str, int lineNumber );

};

#endif
