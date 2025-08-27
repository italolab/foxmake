
#include "Compiler.h"
#include "../util/strutil.h"

#include <vector>
#include <sstream>

using std::vector;
using std::stringstream;

Compiler::Compiler() {
    this->compiler = "";
    this->compilerParams = "";
    this->defines = "";
    this->includeDirs = "";
    this->sourceCodeFile = "";
    this->objectCodeFile = "";
}

string Compiler::buildCMDLine() {
    stringstream ss;
    ss << compiler << " " << compilerParams;

    if ( defines != "" ) {
        vector<string> definesVect = strutil::splitWithDoubleQuotes( defines );

        stringstream defParams;
        for( string define : definesVect )
            defParams << " -D" << define;
        ss << defParams.str();
    }

    if ( includeDirs != "" ) {
        vector<string> includeDirsVect = strutil::splitWithDoubleQuotes( includeDirs );

        stringstream incDirsParams;
        for( string incDir : includeDirsVect )
            incDirsParams << " -I" << incDir;
        ss << incDirsParams.str();
    }

    ss << " -o " << objectCodeFile;
    ss << " -c " << sourceCodeFile;

    return ss.str();
}

string Compiler::getCompiler() {
    return compiler;
}

string Compiler::getCompilerParams() {
    return compilerParams;
}

string Compiler::getDefines() {
    return defines;
}

string Compiler::getIncludeDirs() {
    return includeDirs;
}

string Compiler::getSourceCodeFile() {
    return sourceCodeFile;
}

string Compiler::getObjectCodeFile() {
    return objectCodeFile;
}

void Compiler::setCompiler( string compiler ) {
    this->compiler = compiler;
}

void Compiler::setCompilerParams( string params ) {
    this->compilerParams = params;
}

void Compiler::setDefines( string defines ) {
    this->defines = defines;
}

void Compiler::setIncludeDirs( string dirs ) {
    this->includeDirs = dirs;
}

void Compiler::setSourceCodeFile( string file ) {
    this->sourceCodeFile = file;
}

void Compiler::setObjectCodeFile( string file ) {
    this->objectCodeFile = file;
}