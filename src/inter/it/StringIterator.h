#ifndef STRING_ITERATOR_H
#define STRING_ITERATOR_H

#include "BlockIterator.h"

#include <sstream>

using std::istringstream;

class StringIterator : public BlockIterator {

    private:
        istringstream* stream;

    public:
        StringIterator( string str );
        virtual ~StringIterator();

        bool hasNextLine();
        string nextLine();

};

#endif
