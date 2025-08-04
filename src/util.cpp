
#include "util.h"
#include "appexcept.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <limits>

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
            string path = relativePath( entry.path().string() );
            if ( !filesystem::is_directory( path ) && endsWith( path, ".cpp" ) ) {
                vector<string> dependencies;

                /*
                bool ok = fileDependencies( path, dependencies );
                if ( !ok )
                    return false;

                string headerfile = path;
                headerfile.replace( path.length()-3, 3, "h" );
                if ( filesystem::exists( headerfile ) ) {
                    ok = fileDependencies( headerfile, dependencies );
                    if ( !ok )
                        return false;
                }
                */

                CPPFile* file = new CPPFile;
                file->fileName = path;
                file->dependencies = dependencies;
                cppFiles.push_back( file );
            }
        }
        return true;
    } catch ( const filesystem::filesystem_error& error ) {
        return false;
    }
}

bool fileDependencies( string file, vector<string>& dependencies ) {
    ifstream in( file );
    if ( !in.is_open() ) {
        throw io_error( "Nao foi possivel abrir o arquivo: " + file );
        return false;
    }

    string fname = fileName( file );
    string headerfile;
    if ( endsWith( fname, ".cpp" ) )
        headerfile = fname.replace( fname.length()-3, 3, "h" );
    else headerfile = fname;

    string line;
    while ( getline( in, line ) ) {
        if ( line.find( '{' ) != string::npos )
            break;

        if ( line.find( "#include" ) == 0 ) {
            size_t i = line.find( "\"" );
            size_t j = string::npos;

            if ( i != string::npos )
                j = line.find( "\"", i+1 );

            if ( j != string::npos && j != string::npos ) {
                string hfile = line.substr( i+1, j-i-1 );
                if ( hfile != headerfile ) {
                    string cppfile = directoryPath( file ) + hfile;
                    cppfile.replace( cppfile.length()-1, 1, "cpp" );
                    if ( filesystem::exists( cppfile ))
                        dependencies.push_back( cppfile );
                }
            }
        }
    }
    in.close();
    return true;
}


bool endsWith( string str, string suffix ) {
    int suffixLen = suffix.length();
    int strLen = str.length();
    if ( suffixLen <= strLen ) {
        for( int i = 0; i < suffixLen; i++ )
            if ( suffix[ suffixLen - i - 1 ] != str[ strLen - i - 1 ] )
                return false;
        return true;
    }
    return false;
}

CPPFile* getCPPFileByFileName( vector<CPPFile*>& cppFiles, string fileName ) {
    for( CPPFile* file : cppFiles )
        if ( file->fileName == fileName )
            return file;
    return nullptr;
}

bool existsInVector( vector<string>& vet, string value ) {
    for( string v : vet )
        if ( v == value )
            return true;
    return false;
}

