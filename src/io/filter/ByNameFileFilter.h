#ifndef BY_NAME_FILE_FILTER_H
#define BY_NAME_FILE_FILTER_H

#include "FileFilter.h"

class ByNameFileFilter : public FileFilter {
        
    private:
        string file1;

    public:
        ByNameFileFilter( string fileName );

        bool match( string file );

};

#endif