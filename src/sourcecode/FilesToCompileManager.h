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

        bool loadLastWriteTimesFromFile( map<string, long>& writingTimesElapsedMap, string configFileName );

        void addDependenciesToCompile( vector<CodeInfo*>& filesToCompile, map<string, CodeInfo*>& allSourceInfosMap, string filePath );
        void recursiveLoadDependencies( vector<CodeInfo*>& filesToCompile, map<string, CodeInfo*>& allSourceInfosMap, string filePath );
        bool containsToCompileFile( vector<CodeInfo*>& filesToCompile, string filePath );
        void removeHeaderFiles( vector<CodeInfo*>& filesToCompile );

    public:
        FilesToCompileManager( string sourceFileExtensions, string headerFileExtensions );

        void loadFilesToCompile(
                    vector<CodeInfo*>& filesToCompile,
                    map<string, CodeInfo*>& allSourceInfosMap,
                    string configFilePath );

        bool saveLastWriteTimesInFile(  
                    map<string, CodeInfo*>& allSourceInfosMap, 
                    string configFileName, 
                    bool isAppend = false );

};

#endif
