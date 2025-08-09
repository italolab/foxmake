#ifndef INTER_H
#define INTER_H

#include <string>
#include <stdexcept>

#include "InterManager.h"
#include "InterResult.h"
#include "../darv/Block.h"
#include "../darv/WithPropNo.h"

using std::string;
using std::runtime_error;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

class Inter {

    public:
        virtual InterResult* interpreta( Block* block, string text, int lineNumber, InterManager* manager ) = 0;

        void replaceProps( string& line, int lineNumber, WithPropNo* no );

};

#endif
