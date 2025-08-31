#ifndef LWTIMES_FILE_IO_H
#define LWTIMES_FILE_IO_H

#include "CodeInfo.h"

#include <string>
#include <map>

using std::string;
using std::map;

class LWTimesFileIO {

    public:
        bool loadLastWriteTimesFromFile( 
                map<string, long>& writingTimesElapsedMap, 
                string configFilePath );

        bool saveLastWriteTimesInFile( 
                map<string, CodeInfo*>& allSourceInfosMap, 
                string configFileName, 
                bool isAppend );

};

#endif