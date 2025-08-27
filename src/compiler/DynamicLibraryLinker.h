#ifndef DYNAMIC_LIBRARY_LINKER_H
#define DYNAMIC_LIBRARY_LINKER_H

#include <string>
#include <vector>

using std::string; 
using std::vector;

class DynamicLibraryLinker {

    private:
        string compiler;
        string linkerParams;
        string defines;
        string libraryDirs;
        string libraries;
        string outputFile;

        vector<string>* objectCodeFiles;

        string outputDefFile;
        string outImplibFile;

    public:
        DynamicLibraryLinker();

        string buildCMDLine();

        string getCompiler();
        string getLinkerParams();
        string getDefines();
        string getLibraryDirs();
        string getLibraries();
        string getOutputFile();
        vector<string>& getObjectCodeFiles();
        string getOutputDefFile();
        string getOutImplibFile();

        void setCompiler( string compiler );
        void setLinkerParams( string params );
        void setDefines( string defines );
        void setLibraryDirs( string dirs );
        void setLibraries( string libraries );
        void setOutputFile( string file );
        void setObjectCodeFiles( vector<string>& files );
        void setOutputDefFile( string file );
        void setOutImplibFile( string file );

};

#endif