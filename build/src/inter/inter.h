#ifndef INTER_H
#define INTER_H

#include <string>
#include <stdexcept>

#include "WithPropInter.h"

using std::string;
using std::runtime_error;

class inter_error : public runtime_error {

    public:
        inter_error( string msg );

};

class BlockInter;

class Inter {

    private:
        BlockInter* blockInter;

    public:
        Inter( BlockInter* blockInter );

        string replaceProps( string line, int lineNumber, WithPropInter* inter );

        BlockInter* getBlockInter();

};

#endif // INTER_H
