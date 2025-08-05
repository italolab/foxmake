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


bool createDirectories( string path );
void copyFileOrDirectory( string path, string dir, bool isOverwriteExisting );
void copyFile( string srcFile, string destDir, bool isOverwriteExisting );
void recursiveCopyDir( string srcDir, string destDir, bool isOverwriteExisting );
void deleteFileOrDirectory( string path );
bool deleteFile( string path );
int deleteFiles( string dir );
int recursiveDeleteDirectory( string path );
int recursiveDeleteFilesByExt( string dir, string ext );

string currentPath();
string absolutePath( string path );
string relativePath( string path );
string directoryPath( string path );
string fileOrDirName( string path );
string makePreferred( string path );
string concatPaths( string p1, string p2 );
bool isDirectory( string path );

bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles );
CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName );

#endif
