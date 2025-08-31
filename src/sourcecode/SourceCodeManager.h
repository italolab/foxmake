#ifndef CPP_FILES_MANAGER_H
#define CPP_FILES_MANAGER_H

#include "FilesToCompileManager.h"
#include "DependenciesSCLoader.h"
#include "LWTimesFileIO.h"
#include "CodeInfo.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>

using std::string;
using std::vector;
using std::map;
using std::ifstream;

/*
Essa classe tem os atributos sourceCodeInfosMap, allCodeInfosmap e classToIncludeMap. 

O atributo "sourceCodeInfoMap" é um mapeamento entre o path de cada arquivo de código 
fonte de implementação (.cpp, .c, .cc) e suas informações que estão na struct "CodeInfo".

O atributo "allCodeInfosMap" é um mapeamento entre o path de cada arquivo de código 
fonte, incluíndo os headers também, e suas informações na struct "CodeInfo".

O atributo "classesToIncludeMap" é um mapeamento entre o nome de cada classe e o 
path de seu arquivo.

O método "withHeaderObjectCodeFiles" retorna todos os paths relativos aos arquivos 
objeto de cada arquivo de cabeçalho. Logo, um arquivo de cabeçalho "a/B.h" tem um 
arquivo objeto "a/B.o".
*/

class SourceCodeManager {

    private:
        map<string, CodeInfo*> sourceCodeInfosMap;
        map<string, CodeInfo*> allCodeInfosMap;
        map<string, string> classToIncludeMap;

        string sourceFileExtensions;
        string headerFileExtensions;

        FilesToCompileManager* filesToCompileManager;
        DependenciesSCLoader* dependenciesSCLoader;

        LWTimesFileIO* lwTimesFileIO;

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
