#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "filter/FileFilter.h"
#include "filter/ByExtFileFilter.h"
#include "filter/AllFileFilter.h"

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

char fileSeparator();

class io_error : public runtime_error {
    public:
        io_error( string msg );
};

class joker_error : public io_error {
    public:
        joker_error( string msg );
};

namespace io {

    ByExtFileFilter* by_ext_file_filter( string ext );
    AllFileFilter* all_file_filter();

    bool createDirectories( string path );
    void copyFileOrDirectory( string path, string dir, bool isOverwriteExisting );
    void copyFile( string srcFile, string destDir, bool isOverwriteExisting );
    void copyDir( string srcDir, string destDir, bool isOverwriteExisting );
    void copyFiles( string srcDir, string destDir, FileFilter* filter, bool isOverwriteExisting );
    void recursiveCopyFiles( string srcPath, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting );
    void deleteFileOrDirectory( string path );
    bool deleteFile( string path );
    int deleteDirectory( string path );
    int recursiveDeleteFiles( string dir, FileFilter* filter );

    string currentPath();
    string absolutePath( string path );
    string relativePath( string path );
    string recursiveDirPath( string path );
    string recursiveFileOrDirName( string path );
    string recursiveDirPathToReplace( string path );
    string dirPath( string path );
    string fileOrDirName( string path );
    string addSeparatorToDirIfNeed( string dir );
    string makePreferred( string path );
    string concatPaths( string p1, string p2 );
    string extension( string path );
    string removeRecursiveJoker( string path );

    bool isJokerCopyInPath( string path );
    bool isDirectory( string path );
    bool fileExists( string path );

}

#endif
