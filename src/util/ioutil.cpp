

#include "ioutil.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

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

bool copyFile( string srcFile, string destDir, bool isOverwriteExisting ) {
    try {
        string destDir2 = destDir;
        char ch = destDir[ destDir.length()-1 ];
        if ( ch != '/' && ch != '\\' )
            destDir2 += '/';

        filesystem::path src = makePreferred( srcFile );
        string fname = fileName( srcFile );

        filesystem::path dest = makePreferred( concatPaths( destDir2, fname ) );

        if ( isOverwriteExisting )
            if ( filesystem::exists( dest ) )
                filesystem::remove( dest );

        filesystem::copy_file( src, dest );

        return true;
    } catch ( const filesystem::filesystem_error& e ) {
        cerr << e.what() << endl;
        return false;
    }
}

bool recursiveCopyDir( string srcDir, string destDir, bool isOverwriteExisting ) {
    try {
        filesystem::path src = makePreferred( srcDir );
        filesystem::path dest = makePreferred( destDir );

        filesystem::copy_options options;
        if ( isOverwriteExisting ) {
            options = filesystem::copy_options::recursive | filesystem::copy_options::overwrite_existing;
        } else {
            options = filesystem::copy_options::recursive;
        }

        filesystem::copy( src, dest, options );

        return true;
    } catch ( const filesystem::filesystem_error& e ) {
        return false;
    }
}

string directoryPath( string path ) {
    size_t i = path.find_last_of( filesystem::path::preferred_separator );
    if ( i == string::npos )
        return path;
    return path.substr( 0, i+1 );
}

string fileName( string path ) {
    size_t i = path.find_last_of( filesystem::path::preferred_separator );
    if ( i == string::npos )
        return path;
    return path.substr( i+1, path.length()-i );
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
        return path;
    } else {
        return makePreferred( currentPath() + "/" + path );
    }
}

string relativePath( string path ) {
    filesystem::path p( path );
    if ( p.is_absolute() ) {
        return filesystem::relative( path, currentPath() ).string();
    } else {
        return path;
    }
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
