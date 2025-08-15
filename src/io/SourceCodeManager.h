#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include "FilesToCompileManager.h"
#include "SourceCodeInfo.h"

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
        map<string, SourceCodeInfo*> cppOrCSourceCodeInfosMap;
        map<string, SourceCodeInfo*> headerSourceCodeInfosMap;
        map<string, SourceCodeInfo*> allSourceCodeInfosMap;
        map<string, string> classToIncludeMap;

        FilesToCompileManager* filesToCompileManager;

        bool loadDependencies();
        bool loadDepencenciesForHeaderFile( string headerFilePath );

        bool interpretsInclude( string line, string filePath );
        bool interpretsClasse( ifstream& in, string line, string filePath );

    public:
        SourceCodeManager();

        void loadFilesToCompile( vector<string>& filesToCompile, string configFilePath );
        bool recursiveProcFiles( string srcDir );

        SourceCodeInfo* getCPPOrCSourceCodeInfo( string filePath );
        vector<string> cppOrCFilePaths();
};

#endif
