#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

typedef struct TCPPFile {
    string fileName;
    string objFileName;
} CPPFile;

char fileSeparator();

string currentPath();
string absolutePath( string path );
string relativePath( string path );
string directoryPath( string path );
string fileName( string path );
string makePreferred( string path );
string concatPaths( string p1, string p2 );
bool createDirectories( string path );
bool copyFile( string srcFile, string destDir, bool isOverwriteExisting );
bool recursiveCopyDir( string srcDir, string destDir, bool isOverwriteExisting );

bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles );
CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName );

#endif
