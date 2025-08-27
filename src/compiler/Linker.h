#ifndef LINKER_H
#define LINKER_H

#include <string>
#include <vector>

using std::string; 
using std::vector;

class Linker {

    private:
        string compiler;
        string linkerParams;
        string defines;
        string libraryDirs;
        string libraries;
        string outputFile;
        string resourceFile;

        vector<string>* objectCodeFiles;

    public:
        Linker();

        string buildCMDLine();

        string getCompiler();
        string getLinkerParams();
        string getDefines();
        string getLibraryDirs();
        string getLibraries();
        string getOutputFile();
        vector<string>& getObjectCodeFiles();
        string getResourceFile();

        void setCompiler( string compiler );
        void setLinkerParams( string params );
        void setDefines( string defines );
        void setLibraryDirs( string dirs );
        void setLibraries( string libraries );
        void setOutputFile( string file );
        void setObjectCodeFiles( vector<string>& files );
        void setResourceFile( string file );

};

#endif