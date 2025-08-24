#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "filter/FileFilter.h"
#include "filter/ByNameFileFilter.h"
#include "filter/ByExtFileFilter.h"
#include "filter/AllFileFilter.h"

#include <string>
#include <stdexcept>
#include <vector>

class io_error : public runtime_error {
    public:
        io_error( string msg );
};

class joker_error : public io_error {
    public:
        joker_error( string msg );
};

namespace io {

    ByNameFileFilter* by_name_file_filter( string file );
    ByExtFileFilter* by_ext_file_filter( string ext );
    AllFileFilter* all_file_filter();

    bool createDir( string path );
    bool createDirs( string path );
    void copyFileOrDirectory( string srcPath, string destDir, bool isOverwriteExisting, bool isRecursive );
    void copyFile( string srcFile, string destDir, bool isOverwriteExisting );
    void copyDir( string srcDir, string destDir, bool isOverwriteExisting, bool isRecursive );
    void copyFiles( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting );
    void recursiveCopyFiles( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting );
    bool deleteFileOrDirectory( string path );
    int recursiveDeleteDirectory( string path );
    int recursiveDeleteFileOrDirectory( string path );
    int recursiveDeleteFilesOnly( string dir, FileFilter* filter );
    int recursiveDeleteDirectoryContent( string dir );

    string currentPath();
    string absolutePath( string path );
    string relativePath( string path );
    string parentPath( string path );
    string recursiveDirPath( string path );
    string recursiveFileOrDirName( string path );
    string recursiveDirPathToReplace( string path );
    string dirPath( string path );
    string fileOrDirName( string path );
    string fileNameWithoutExtension( string pathOrName );
    string addSeparatorToDirIfNeed( string dir );
    string makePreferred( string path );
    string extension( string path );
    string removeRecursiveJoker( string path );
    string removeDirContentJoker( string path );
    string removeInitTwoDotsAndSlash( string relativePath );
    char fileSeparator();

    string resolvePath( string currDir, string path );
    string resolvePath( string path );
    string absoluteResolvePath( string path );

    bool isJokerInPath( string path );
    bool isDir( string path );
    bool isEmptyDir( string dir );
    bool fileExists( string path );

    long lastWriteTime( string path );

}

#endif
