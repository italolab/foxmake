#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "filter/FileFilter.h"
#include "filter/ByNameFileFilter.h"

#include <string>
#include <stdexcept>
#include <vector>

using std::runtime_error;

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

    bool createDir( string path );
    bool createDirs( string path );
    void copyFile( string srcFile, string destFile, bool isOverwriteExisting );
    void copyDir( string srcDir, string destDir, bool isOverwriteExisting, bool isRecursive );
    void copyFileOrDirectoryToDir( string srcPath, string destDir, bool isOverwriteExisting, bool isRecursive );
    void copyFileToDir( string srcFile, string destDir, bool isOverwriteExisting );
    void copyDirToDir( string srcDir, string destDir, bool isOverwriteExisting, bool isRecursive );
    void copyFilesToDir( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting );
    void recursiveCopyFilesToDir( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting );
    bool deleteFileOrDirectory( string path );
    int deleteFiles( string path, FileFilter* filter );
    int recursiveDeleteFiles( string dir, FileFilter* filter );
    int recursiveDeleteDirectory( string path );
    int recursiveDeleteFileOrDirectory( string path );
    int recursiveDeleteDirectoryContent( string dir );

    void writeInTextFile( string file, string text );
    string readFromTextFile( string file );

    bool isDir( string path );
    bool isFile( string path );
    bool isEmptyDir( string dir );
    bool fileExists( string path );
    
    long lastWriteTime( string path );


namespace path {
    string currentPath();
    string absolutePath( string path );
    string relativePath( string path );
    string parentPath( string path );
    string dirPath( string path );
    string fileOrDirName( string path );
    string fileOrDirNameWithoutExtension( string pathOrName );
    string addSeparatorToDirIfNeed( string dir );
    string removeSeparatorFromDirIfNeed( string dir );
    string makePreferred( string path );
    string makeUnixPreferred( string path );
    string extension( string path );
    char preferredSeparator();

    string jokerJokerDirPath( string path );
    string jokerJokerAfterPath( string path );
    string jokerJokerBeforePath( string path );
    string removeJokerJoker( string path );

    bool isJokerInPath( string path );

    string resolvePath( string currDir, string path );
    string resolvePath( string path );
    string absoluteResolvePath( string path );

    string removeInitTwoDotsAndSlash( string relativePath );

}

}

#endif
