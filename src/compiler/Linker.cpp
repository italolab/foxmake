
#include "Linker.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;

Linker::Linker() {
    this->compiler = "";
    this->linkerParams = "";
    this->defines = "";
    this->libraryDirs = "";
    this->libraries = "";
    this->outputFile = "";
    this->resourceFile = "";
    this->objectCodeFiles = new vector<string>(0);
}

string Linker::buildCMDLine() {
    stringstream ss;
    ss << compiler;

    ss << " -o " << outputFile;    

    if ( defines != "" ) {
        vector<string> definesVect = strutil::splitWithDoubleQuotes( defines );

        stringstream defParams;
        for( string define : definesVect )
            defParams << " -D" << define;
        ss << defParams.str();
    }

    for( string objFile : *objectCodeFiles )
        ss << " " << objFile;    

    if ( resourceFile != "" )
        ss << " " << resourceFile;

    vector<string> libdirsVect = strutil::splitWithDoubleQuotes( libraryDirs );
    vector<string> libsVect = strutil::splitWithDoubleQuotes( libraries );

    stringstream libdirParams;
    stringstream libParams;
    string token;

    for( string libdir : libdirsVect)
        libdirParams << " -L" << libdir;

    for( string lib : libsVect )
        libParams << " -l" << lib;

    ss << libdirParams.str() << libParams.str();

    ss << " " << linkerParams;

    return ss.str();
}

string Linker::getCompiler() {
    return compiler;
}

string Linker::getLinkerParams() {
    return linkerParams;
}

string Linker::getDefines() {
    return defines;
}

string Linker::getLibraryDirs() {
    return libraryDirs;
}

string Linker::getLibraries() {
    return libraries;
}

string Linker::getOutputFile() {
    return outputFile;
}

vector<string>& Linker::getObjectCodeFiles() {
    return *objectCodeFiles;
}

string Linker::getResourceFile() {
    return resourceFile;
}

void Linker::setCompiler( string compiler ) {
    this->compiler = compiler;
}

void Linker::setLinkerParams( string params ) {
    this->linkerParams = params;
}

void Linker::setDefines( string defines ) {
    this->defines = defines;
}

void Linker::setLibraryDirs( string dirs ) {
    this->libraryDirs = dirs;
}

void Linker::setLibraries( string libraries ) {
    this->libraries = libraries;
}

void Linker::setOutputFile( string file ) {
    this->outputFile = file;
}

void Linker::setObjectCodeFiles( vector<string>& files ) {
    this->objectCodeFiles = &files;
}

void Linker::setResourceFile( string file ) {
    this->resourceFile = file;
}