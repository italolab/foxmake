#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include "FilesToCompileManager.h"

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

class SourceCodeManager {

    private:
        map<string, SourceCodeInfo*> scInfosMap;
        map<string, vector<string>> dependenciesMap;
        vector<string> allSourceCodeFiles;
        FilesToCompileManager* filesToCompileManager;

        bool loadDependencies();
        bool loadDepencenciesForHeaderFile( string headerFilePath );

    public:
        SourceCodeManager();

        void loadFilesToCompile( vector<string>& filesToCompile, string configFilePath );
        bool recursiveProcFiles( string srcDir );

        SourceCodeInfo* getSourceCodeInfo( string filePath );
        vector<string> sourceCodeFilePaths();

        vector<string>& getDepencenciesForHeaderFile( string filePath );
        bool isHeaderFileLoaded( string filePath );

};

#endif
