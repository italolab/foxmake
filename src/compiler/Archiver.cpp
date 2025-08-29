
#include "Archiver.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;

Archiver::Archiver() {
    this->archiver = "";
    this->defines = "";
    this->libraryDirs = "";
    this->libraries = "";
    this->outputFile = "";
    this->objectCodeFiles = new vector<string>(0);
}

string Archiver::buildCMDLine() {
    stringstream ss;
    ss << archiver << " -r -s ";

    if ( defines != "" ) {
        vector<string> definesVect = strutil::splitWithDoubleQuotes( defines );

        stringstream defParams;
        for( string define : definesVect )
            defParams << " -D" << define;
        ss << defParams.str();
    }

    ss << " " << outputFile;
    
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

    ss << " " << archiverParams;

    return ss.str();
}

string Archiver::getArchiver() {
    return archiver;
}

string Archiver::getArchiverParams() {
    return archiverParams;
}

string Archiver::getDefines() {
    return defines;
}

string Archiver::getLibraryDirs() {
    return libraryDirs;
}

string Archiver::getLibraries() {
    return libraries;
}

string Archiver::getOutputFile() {
    return outputFile;
}

vector<string>& Archiver::getObjectCodeFiles() {
    return *objectCodeFiles;
}

void Archiver::setArchiver( string archiver ) {
    this->archiver = archiver;
}

void Archiver::setArchiverParams( string params ) {
    this->archiverParams = params;
}

void Archiver::setDefines( string defines ) {
    this->defines = defines;
}

void Archiver::setLibraryDirs( string dirs ) {
    this->libraryDirs = dirs;
}

void Archiver::setLibraries( string libraries ) {
    this->libraries = libraries;
}

void Archiver::setOutputFile( string file ) {
    this->outputFile = file;
}

void Archiver::setObjectCodeFiles( vector<string>& files ) {
    this->objectCodeFiles = &files;
}
