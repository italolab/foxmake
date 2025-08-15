#ifndef FILES_TO_COMPILE_MANAGER_H
#define FILES_TO_COMPILE_MANAGER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class FilesToCompileManager {

    private:
        bool loadWritingTimesElapsedFile( map<string, long>& writingTimesElapsedMap, string configFileName );
        bool saveWritingTimesElapsedInFile(  vector<string>& sourceFiles, string configFileName );

        void addDependenciesToCompile( vector<string>& filesToCompile, map<string, vector<string>>& depsMap, string filePath );
        void recursiveLoadDependencies( vector<string>& filesToCompile, map<string, vector<string>>& depsMap, string fileName );
        bool containsInVector( vector<string>& vect, string filePath );

    public:
        void loadFilesToCompile( vector<string>& filesToCompile, vector<string>& sourceFiles, map<string, vector<string>>& depsMap, string configFilePath );

};

#endif
