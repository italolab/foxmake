#ifndef FILES_TO_COMPILE_MANAGER_H
#define FILES_TO_COMPILE_MANAGER_H

#include "SourceCodeInfo.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class FilesToCompileManager {

    private:
        bool loadWritingTimesElapsedFile( map<string, long>& writingTimesElapsedMap, string configFileName );
        bool saveWritingTimesElapsedInFile(  map<string, SourceCodeInfo*>& allSourceInfos, string configFileName );

        void addDependenciesToCompile( vector<string>& filesToCompile, map<string, SourceCodeInfo*>& allSourceInfos, string filePath );
        void recursiveLoadDependencies( vector<string>& filesToCompile, map<string, SourceCodeInfo*>& allSourceInfos, string fileName );
        bool containsInVector( vector<string>& vect, string filePath );

    public:
        void loadFilesToCompile(
                    vector<string>& filesToCompile,
                    map<string, SourceCodeInfo*>& allSourceInfos,
                    string configFilePath );

};

#endif
