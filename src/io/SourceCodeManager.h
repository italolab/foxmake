#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include "FilesToCompileManager.h"
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
        map<string, CodeInfo*> headerCodeInfosMap;
        map<string, CodeInfo*> allCodeInfosMap;
        map<string, string> classToIncludeMap;

        string sourceFileExtensions;
        string headerFileExtensions;

        FilesToCompileManager* filesToCompileManager;

        bool loadDependencies();
        bool loadDepencenciesForFile( string headerFilePath );

        bool interpretsInclude( string line, string filePath );
        bool interpretsClasse( ifstream& in, string line, string filePath );

    public:
        SourceCodeManager( string sourceFileExtensions, string headerFileExtensions );

        void loadFilesToCompile( vector<CodeInfo*>& filesToCompile, string configFilePath );
        void saveWritingTimeElapsedInFile( string configFilePath );
        bool recursiveProcFiles( string srcDir );

        CodeInfo* getSourceCodeInfo( string filePath );
        vector<string> sourceFilePaths();
        vector<CodeInfo*> sourceCodeInfos();

};

#endif
