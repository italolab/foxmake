#ifndef FILE_ITERATOR_H
#define FILE_ITERATOR_H

#include "BlockIterator.h"

#include <fstream>

using namespace std;

namespace fileit {

    class file_not_open_error : runtime_error {
        public:
            file_not_open_error( string msg );
    };

}

class FileIterator : public BlockIterator {

    private:
        ifstream* stream;

    public:
        FileIterator( string file );

        bool hasNextLine();
        string nextLine();

};

#endif
