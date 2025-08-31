#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include "FilesToCompileManager.h"
#include "DependenciesSCLoader.h"
#include "CodeInfo.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>

using std::string;
using std::vector;
using std::map;
using std::ifstream;

class SourceCodeManager {

    private:
        map<string, CodeInfo*> sourceCodeInfosMap;
        map<string, CodeInfo*> allCodeInfosMap;
        map<string, string> classToIncludeMap;

        string sourceFileExtensions;
        string headerFileExtensions;

        FilesToCompileManager* filesToCompileManager;
        DependenciesSCLoader* dependenciesSCLoader;

    public:
        SourceCodeManager( string sourceFileExtensions, string headerFileExtensions );
        virtual ~SourceCodeManager();

        bool recursiveProcFiles( string srcDir, string targetFolder );
        void loadFilesToCompile( vector<CodeInfo*>& filesToCompile, string configFilePath );
        void saveLastWriteTimesInFile( string configFilePath, bool isAppend );

        CodeInfo* getSourceCodeInfo( string filePath );
        vector<string> withHeaderObjectCodeFiles();        
        vector<string> sourceFilePaths();
        vector<CodeInfo*> sourceCodeInfos();

};

#endif
