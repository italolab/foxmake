#ifndef STATIC_LIBRARY_LINKER_H
#define STATIC_LIBRARY_LINKER_H

#include <string>
#include <vector>

using std::string; 
using std::vector;

class Archiver {

    private:
        string archiver;
        string archiverParams;
        string defines;
        string libraryDirs;
        string libraries;
        string outputFile;

        vector<string>* objectCodeFiles;

    public:
        Archiver();

        string buildCMDLine();

        string getArchiver();
        string getArchiverParams();
        string getDefines();
        string getLibraryDirs();
        string getLibraries();
        string getOutputFile();
        vector<string>& getObjectCodeFiles();

        void setArchiver( string archiver );
        void setArchiverParams( string params );
        void setDefines( string defines );
        void setLibraryDirs( string dirs );
        void setLibraries( string libraries );
        void setOutputFile( string file );
        void setObjectCodeFiles( vector<string>& files );

};

#endif