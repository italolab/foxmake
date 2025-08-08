#ifndef FILE_FILTER_H
#define FILE_FILTER_H

#include <string>

class FileFilter {

    public:
        virtual bool isFilter( std::string file ) = 0;

};

#endif // FILE_FILTER_H
