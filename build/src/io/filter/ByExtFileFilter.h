#ifndef BY_EXT_FILE_FILTER_H
#define BY_EXT_FILE_FILTER_H

#include "FileFilter.h"
#include <string>

using namespace std;

class ByExtFileFilter : public FileFilter {

    private:
        string ext;

    public:
        ByExtFileFilter( string ext );

        bool isFilter( string file );

};

#endif
