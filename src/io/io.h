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

    ByNameFileFilter* by_name_file_filter( string fileName );

    bool createDir( string path );
    bool createDirs( string path );

    int countFilesAndDirs( string dir );
    
    void copyFile( string srcFile, string destFile, bool isOverwriteExisting );

    void copyDir( 
                string srcDir, 
                string targetDir, 
                bool isOverwriteExisting, 
                bool isRecursive );

    void copyFileOrDir( 
        string srcPath, 
        string targetDir, 
        bool isOverwriteExisting, 
        bool isRecursive );
    
    void copyFiles(
                string srcDir, 
                string targetDir, 
                FileFilter* filter, 
                bool isOverwriteExisting, 
                bool isRecursive );

    void copyFiles( 
                string srcDir, 
                string targetDir, 
                string forReplacePath, 
                FileFilter* filter, 
                bool isOverwriteExisting, 
                bool isRecursive );
    
    bool hasNoEmptyDir( string path, FileFilter* filter, bool isRecursive );

    int deleteFileOrDir( string path, bool isRecursive );
    int deleteFiles( string dir, FileFilter* filter, bool isRecursive );
    int recursiveDeleteDir( string dir );
        
    void writeInTextFile( string file, string text );
    string readFromTextFile( string file );

    bool isDir( string path );
    bool isFile( string path );
    bool isEmptyDir( string dir );
    bool fileExists( string path );
    
    long lastWriteTime( string path );

namespace path {
    
    string currentPath();
    string tempDirPath();
    string absolutePath( string path );
    string relativePath( string path );
    string parentPath( string path );
    string dirPath( string path );
    string fileOrDirName( string path );
    string fileOrDirNameWithoutExtension( string pathOrName );
    string addSeparatorIfNeed( string dir );
    string removeSeparatorFromDirIfNeed( string dir );
    string makePreferred( string path );
    string makeUnixPreferred( string path );
    string extension( string path );
    char preferredSeparator();

    string jokerJokerDirPath( string path );
    string jokerJokerAfterPath( string path );
    string jokerJokerBeforePath( string path );
    string removeJokerJoker( string path );

    bool isFileNameStartsWithJoker( string path );

    string resolvePath( string currDir, string path );
    string resolvePath( string path );
    string absoluteResolvePath( string path );

    string removeInitTwoDotsAndSlashes( string relativePath );

}

}

#endif
