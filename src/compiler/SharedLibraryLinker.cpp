
#include "SharedLibraryLinker.h"
#include "../util/strutil.h"

#include <vector>
#include <sstream>

using std::vector;
using std::stringstream;

SharedLibraryLinker::SharedLibraryLinker() {
    this->compiler = "";
    this->linkerParams = "";
    this->defines = "";
    this->libraryDirs = "";
    this->libraries = "";
    this->outputFile = "";
    this->outImplibFile = "";
    this->outputDefFile = "";
    this->objectCodeFiles = new vector<string>(0);
}

string SharedLibraryLinker::buildCMDLine() {
    stringstream ss;
    ss << compiler;

    ss << " -shared";
    if ( outputDefFile != "" )
        ss << " -Wl,--output-def=" << outputDefFile;
    if ( outImplibFile != "" )
        ss << " -Wl,--out-implib=" << outImplibFile;

    if ( defines != "" ) {
        vector<string> definesVect = strutil::splitWithDoubleQuotes( defines );

        stringstream defParams;
        for( string define : definesVect )
            defParams << " -D" << define;
        ss << defParams.str();
    }

    ss << " -o " << outputFile;
    
    for( string objFile : *objectCodeFiles )
        ss << " " << objFile;    

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


string SharedLibraryLinker::getCompiler() {
    return compiler;
}

string SharedLibraryLinker::getLinkerParams() {
    return linkerParams;
}

string SharedLibraryLinker::getDefines() {
    return defines;
}

string SharedLibraryLinker::getLibraryDirs() {
    return libraryDirs;
}

string SharedLibraryLinker::getLibraries() {
    return libraries;
}

string SharedLibraryLinker::getOutputFile() {
    return outputFile;
}

vector<string>& SharedLibraryLinker::getObjectCodeFiles() {
    return *objectCodeFiles;
}

string SharedLibraryLinker::getOutputDefFile() {
    return outputDefFile;
}

string SharedLibraryLinker::getOutImplibFile() {
    return outImplibFile;
}

void SharedLibraryLinker::setCompiler( string compiler ) {
    this->compiler = compiler;
}

void SharedLibraryLinker::setLinkerParams( string params ) {
    this->linkerParams = params;
}

void SharedLibraryLinker::setDefines( string defines ) {
    this->defines = defines;
}

void SharedLibraryLinker::setLibraryDirs( string dirs ) {
    this->libraryDirs = dirs;
}

void SharedLibraryLinker::setLibraries( string libraries ) {
    this->libraries = libraries;
}

void SharedLibraryLinker::setOutputFile( string file ) {
    this->outputFile = file;
}

void SharedLibraryLinker::setObjectCodeFiles( vector<string>& files ) {
    this->objectCodeFiles = &files;
}

void SharedLibraryLinker::setOutputDefFile( string file ) {
    this->outputDefFile = file;
}

void SharedLibraryLinker::setOutImplibFile( string file ) {
    this->outImplibFile = file;
}