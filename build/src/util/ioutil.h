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
void copyDir( string srcDir, string destDir, bool isOverwriteExisting );
void copyFilesByExt( string srcDir, string ext, string destDir, bool isOverwriteExisting );
void deleteFileOrDirectory( string path );
bool deleteFile( string path );
int deleteFiles( string dir );
int deleteDirectory( string path );
int deleteFilesByExt( string dir, string ext );

string currentPath();
string absolutePath( string path );
string relativePath( string path );
string directoryPath( string path );
string directoryPath( string path, bool& recursive );
string fileOrDirName( string path );
string addSeparatorToDirIfNeed( string dir );
string makePreferred( string path );
string concatPaths( string p1, string p2 );
bool isDirectory( string path );

bool fileExists( string path );

bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles );
CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName );

#endif
