#ifndef SCRIPT_PROPERTY_MANAGER_H
#define SCRIPT_PROPERTY_MANAGER_H

#include "../darv/MainScript.h"

class ScriptPropertyManager {

    private:
        void* mgr;

    public:
        ScriptPropertyManager( void* mgr );

        string getCompiler();
        string getArchiver();

        string getBaseDir();
        string getSrcDir();
        string getTestDir();
        string getBinDir();
        string getObjDir();
        string getBuildDir();

        string getOutputFileName();
        string getBuildFiles();
        string getResourceFile();

        string getCompilerParams();
        string getLinkerParams();
        string getArchiverParams();

        
        string getLibDirs();
        string getIncludeDirs();
        string getLibs();

        string getDefines();

        string getTestCompilerParams();
        string getTestLinkerParams();
        string getTestLibDirs();
        string getTestIncludeDirs();
        string getTestLibs();
        string getTestDefines();
        
        string getOutputDefFile();
        string getOutImplibFile();

};

#endif