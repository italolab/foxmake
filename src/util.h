#ifndef UTIL2_H
#define UTIL2_H

#include <string>
#include <vector>

using namespace std;

typedef struct TCPPFile {
    string fileName;
    vector<string> dependencies;
} CPPFile;

bool endsWith( string str, string suffix );

string currentPath();
string absolutePath( string path );
string relativePath( string path );
string directoryPath( string path );
string fileName( string path );
string makePreferred( string path );
bool recursiveProcSrcFiles( string basedir, vector<CPPFile>& cppFiles );
bool fileDependencies( string file, vector<string>& dependencies );


#endif
