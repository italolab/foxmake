#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>

using std::string; 
using std::vector;

class Compiler {

    private:
        string compiler;
        string compilerParams;
        string defines;
        string includeDirs;
        string sourceCodeFile;
        string objectCodeFile;

    public:
        Compiler();
        
        string buildCMDLine();

        string getCompiler();
        string getCompilerParams();
        string getDefines();
        string getIncludeDirs();
        string getSourceCodeFile();
        string getObjectCodeFile();

        void setCompiler( string compiler );
        void setCompilerParams( string params );
        void setDefines( string defines );
        void setIncludeDirs( string dirs );
        void setSourceCodeFile( string file );
        void setObjectCodeFile( string file );

};

#endif