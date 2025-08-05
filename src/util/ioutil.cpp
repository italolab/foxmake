

#include "ioutil.h"
#include "util.h"
#include "utilexcept.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

void copyFileOrDirectory( string path, string dir, bool isOverwriteExisting ) {
    if ( isDirectory( path ) ) {
        recursiveCopyDir( path, dir, isOverwriteExisting );
    } else {
        copyFile( path, dir, isOverwriteExisting );
    }
}

void deleteFileOrDirectory( string path ) {
    if ( isDirectory( path ) ) {
        recursiveDeleteDirectory( path );
    } else {
        deleteFile( path );
    }
}

int recursiveDeleteFilesByExt( string dir, string ext ) {
    int removedCount = 0;
    try {
        string path = makePreferred( dir );
        for( const auto& entry : filesystem::recursive_directory_iterator( path ) ) {
            string file = makePreferred( entry.path().string() );
            if ( !filesystem::is_directory( file ) && endsWith( file, ext ) ) {
                deleteFile( file );
                removedCount++;
            }
        }
    } catch ( const filesystem::filesystem_error& e ) {
        throw io_error( e.what() );
    }
    return removedCount;
}

bool deleteFile( string path ) {
    try {
        return filesystem::remove( makePreferred( path ) );
    } catch ( const filesystem::filesystem_error& e ) {
        return false;
    }
}

int deleteFiles( string path ) {
    int removedCount = 0;
    try {
        for( const auto& entry : filesystem::recursive_directory_iterator( path ) ) {
            string file = makePreferred( entry.path().string() );
            if ( filesystem::is_directory( file ) ) {
                removedCount += recursiveDeleteDirectory( file );
            } else {
                deleteFile( file );
                removedCount++;
            }
        }
    } catch ( const filesystem::filesystem_error& e ) {
        throw io_error( e.what() );
    }
    return removedCount;
}

int recursiveDeleteDirectory( string path ) {
    try {
        string p = makePreferred( path );
        if ( filesystem::exists( p ) ) {
            uintmax_t removedCount = filesystem::remove_all( p );
            return removedCount;
        }
        return 0;
    } catch ( const filesystem::filesystem_error& e ) {
        throw io_error( e.what() );
    }
}

string concatPaths( string p1, string p2 ) {
    string path = p1;
    char ch = path[ path.length()-1 ];
    if ( ch != '/' && ch != '\\' )
        path += '/';
    path += p2;
    return makePreferred( path );
}

bool createDirectories( string path ) {
    filesystem::path dirpath = makePreferred( path );
    return filesystem::create_directories( dirpath );
}

void copyFile( string srcFile, string destDir, bool isOverwriteExisting ) {
    try {
        string destDir2 = destDir;
        char ch = destDir[ destDir.length()-1 ];
        if ( ch != '/' && ch != '\\' )
            destDir2 += '/';

        filesystem::path src = makePreferred( srcFile );
        string fname = fileOrDirName( srcFile );

        filesystem::path dest = makePreferred( concatPaths( destDir2, fname ) );

        if ( isOverwriteExisting )
            if ( filesystem::exists( dest ) )
                filesystem::remove( dest );

        filesystem::copy_file( src, dest );
    } catch ( const filesystem::filesystem_error& e ) {
        throw io_error( e.what() );
    }
}

void recursiveCopyDir( string srcDir, string destDir, bool isOverwriteExisting ) {
    try {
        string fsrcName = fileOrDirName( srcDir );

        filesystem::path src = makePreferred( srcDir );
        filesystem::path dest = makePreferred( concatPaths( destDir, fsrcName ) );

        filesystem::copy_options options;
        if ( isOverwriteExisting ) {
            options = filesystem::copy_options::recursive | filesystem::copy_options::overwrite_existing;
        } else {
            options = filesystem::copy_options::recursive;
        }

        if ( filesystem::exists( dest ) )
            filesystem::remove_all( dest );

        filesystem::copy( src, dest, options );
    } catch ( const filesystem::filesystem_error& e ) {
        throw io_error( e.what() );
    }
}

string directoryPath( string path ) {
    size_t i = path.find_last_of( filesystem::path::preferred_separator );
    if ( i == string::npos )
        return path;
    return path.substr( 0, i+1 );
}

string fileOrDirName( string path ) {
    string p = makePreferred( path );
    size_t i = p.find_last_of( filesystem::path::preferred_separator );
    if ( i == string::npos )
        return p;

    if ( filesystem::is_directory( p ) ) {
        size_t j = p.find_last_of( filesystem::path::preferred_separator, i-1 );
        size_t k = ( j == string::npos ? 0 : j+1 );
        return p.substr( k, j-i-1 );
    }
    return p.substr( i+1, p.length()-i );
}

char fileSeparator() {
    return filesystem::path::preferred_separator;
}

string currentPath() {
    filesystem::path currPathFS = filesystem::current_path();
    return currPathFS.string();
}

string makePreferred( string path ) {
    filesystem::path p( path );
    p.make_preferred();
    return p.string();
}

string absolutePath( string path ) {
    filesystem::path p( path );
    if ( p.is_absolute() ) {
        return makePreferred( path );
    } else {
        return makePreferred( currentPath() + "/" + path );
    }
}

string relativePath( string path ) {
    filesystem::path p( path );
    if ( p.is_absolute() ) {
        return filesystem::relative( path, currentPath() ).string();
    } else {
        return makePreferred( path );
    }
}

bool isDirectory( string path ) {
    return filesystem::is_directory( path );
}

bool recursiveProcSrcFiles( string basedir, vector<CPPFile*>& cppFiles ) {
    string prefBaseDir = makePreferred( basedir );
    try {
        for( const auto& entry : filesystem::recursive_directory_iterator( prefBaseDir ) ) {
            string fileName = relativePath( entry.path().string() );
            fileName = makePreferred( fileName );
            if ( !filesystem::is_directory( fileName ) && endsWith( fileName, ".cpp" ) ) {
                string objFileName = fileName;
                objFileName.replace( objFileName.length()-3, 3, "o" );

                CPPFile* file = new CPPFile;
                file->fileName = fileName;
                file->objFileName = objFileName;
                cppFiles.push_back( file );
            }
        }
        return true;
    } catch ( const filesystem::filesystem_error& error ) {
        return false;
    }
}

CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName ) {
    for( CPPFile* file : cppFiles )
        if ( file->fileName == fileName )
            return file;
    return nullptr;
}
