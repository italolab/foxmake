#ifndef FILE_FILTER_H
#define FILE_FILTER_H

#include <string>

using std::string;

class FileFilter {

    public:
        virtual bool match( string file ) = 0;

};

#endif
