#ifndef FILES_TO_COMPILE_MANAGER_H
#define FILES_TO_COMPILE_MANAGER_H

#include "CodeInfo.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class FilesToCompileManager {

    private:
        string sourceFileExtensions;
        string headerFileExtensions;

        bool loadWritingTimesElapsedFile( map<string, long>& writingTimesElapsedMap, string configFileName );
        bool saveWritingTimesElapsedInFile(  map<string, CodeInfo*>& allSourceInfos, string configFileName );

        void addDependenciesToCompile( vector<CodeInfo*>& filesToCompile, map<string, CodeInfo*>& allSourceInfos, string filePath );
        void recursiveLoadDependencies( vector<CodeInfo*>& filesToCompile, map<string, CodeInfo*>& allSourceInfos, string filePath );
        bool containsToCompileFile( vector<CodeInfo*>& filesToCompile, string filePath );
        void removeHeaderFiles( vector<CodeInfo*>& filesToCompile );

    public:
        FilesToCompileManager( string sourceFileExtensions, string headerFileExtensions );

        void loadFilesToCompile(
                    vector<CodeInfo*>& filesToCompile,
                    map<string, CodeInfo*>& allSourceInfos,
                    string configFilePath );

};

#endif
