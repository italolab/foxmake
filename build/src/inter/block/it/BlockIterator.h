#ifndef BLOCK_ITERATOR_H
#define BLOCK_ITERATOR_H

#include <string>

using std::string;

class BlockIterator {

    public:
        virtual bool hasNextLine() = 0;
        virtual string nextLine() = 0;

};

#endif
