#ifndef ALL_FILE_FILTER_H
#define ALL_FILE_FILTER_H

#include "FileFilter.h"

#include <string>

class AllFileFilter : public FileFilter {

    public:
        bool isFilter( std::string file );

};

#endif
