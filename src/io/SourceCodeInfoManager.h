#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

typedef struct TSourceCodeInfo {
    string filePath;
    string objFilePath;
} SourceCodeInfo;

class SourceCodeInfoManager {

    private:
        map<string, SourceCodeInfo*> scInfosMap;
        map<string, vector<string>> dependenciesMap;
        vector<string> allSourceCodeFiles;

        bool loadDependencies();
        bool loadDepencenciesForHeaderFile( string headerFilePath );

        bool loadLastWriteTimesFromFile( map<string, long>& lwTimesMap, string configFileName );
        bool saveLastWriteTimesInFile( string configFileName );

        void addDependenciesToCompile( vector<string>& filesToComp, string filePath );
        bool containsFileToCompile( vector<string>& filesToComp, string filePath );

    public:
        bool recursiveProcFiles( string srcDir );

        SourceCodeInfo* getSourceCodeInfo( string filePath );
        vector<string> sourceCodeFilePaths();

        vector<string>& getDepencenciesForHeaderFile( string filePath );
        bool isHeaderFileLoaded( string filePath );

        void loadFilesToCompile( vector<string>& filesToComp, string configFilePath );

};

#endif
