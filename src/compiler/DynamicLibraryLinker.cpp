
#include "DynamicLibraryLinker.h"
#include "../util/strutil.h"

#include <vector>
#include <sstream>

using std::vector;
using std::stringstream;

DynamicLibraryLinker::DynamicLibraryLinker() {
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

string DynamicLibraryLinker::buildCMDLine() {
    stringstream ss;
    ss << compiler;

    ss << " -shared";
    if ( outputDefFile != "" )
        ss << " -Wl,--output-def=" << outputDefFile;
    if ( outImplibFile != "" )
        ss << " -Wl,--out-implib=" << outImplibFile;

    if ( strutil::endsWith( outputFile, ".dll" ) )
        ss << " -Wl,--dll";

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


string DynamicLibraryLinker::getCompiler() {
    return compiler;
}

string DynamicLibraryLinker::getLinkerParams() {
    return linkerParams;
}

string DynamicLibraryLinker::getDefines() {
    return defines;
}

string DynamicLibraryLinker::getLibraryDirs() {
    return libraryDirs;
}

string DynamicLibraryLinker::getLibraries() {
    return libraries;
}

string DynamicLibraryLinker::getOutputFile() {
    return outputFile;
}

vector<string>& DynamicLibraryLinker::getObjectCodeFiles() {
    return *objectCodeFiles;
}

string DynamicLibraryLinker::getOutputDefFile() {
    return outputDefFile;
}

string DynamicLibraryLinker::getOutImplibFile() {
    return outImplibFile;
}

void DynamicLibraryLinker::setCompiler( string compiler ) {
    this->compiler = compiler;
}

void DynamicLibraryLinker::setLinkerParams( string params ) {
    this->linkerParams = params;
}

void DynamicLibraryLinker::setDefines( string defines ) {
    this->defines = defines;
}

void DynamicLibraryLinker::setLibraryDirs( string dirs ) {
    this->libraryDirs = dirs;
}

void DynamicLibraryLinker::setLibraries( string libraries ) {
    this->libraries = libraries;
}

void DynamicLibraryLinker::setOutputFile( string file ) {
    this->outputFile = file;
}

void DynamicLibraryLinker::setObjectCodeFiles( vector<string>& files ) {
    this->objectCodeFiles = &files;
}

void DynamicLibraryLinker::setOutputDefFile( string file ) {
    this->outputDefFile = file;
}

void DynamicLibraryLinker::setOutImplibFile( string file ) {
    this->outImplibFile = file;
}