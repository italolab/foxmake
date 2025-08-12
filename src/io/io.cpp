

#include "io.h"
#include "../util/strutil.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

io_error::io_error( string msg ) : runtime_error( msg ) {}
joker_error::joker_error( string msg ) : io_error( msg ) {}

namespace io {

    ByExtFileFilter* by_ext_file_filter( string ext ) {
        return new ByExtFileFilter( ext );
    }

    AllFileFilter* all_file_filter() {
        return new AllFileFilter();
    }

    bool deleteFileOrDirectory( string path ) {
        string p = makePreferred( path );
        try {
            return filesystem::remove( p );
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    int recursiveDeleteFilesOnly( string dir, FileFilter* filter ) {
        int removedCount = 0;
        try {
            string dirpath = makePreferred( dir );
            for( const auto& entry : filesystem::recursive_directory_iterator( dirpath ) ) {
                string file = makePreferred( entry.path().string() );

                if ( filter != nullptr )
                    if ( !filter->isFilter( file ) )
                        continue;

                if ( !filesystem::is_directory( file ) ) {
                    deleteFileOrDirectory( file );
                    removedCount++;
                }
            }
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
        return removedCount;
    }

    int recursiveDeleteDirectoryContent( string dir ) {
        int removedCount = 0;
        try {
            string dirpath = makePreferred( dir );
            for( const auto& entry : filesystem::directory_iterator( dirpath ) ) {
                string file = makePreferred( entry.path().string() );
                removedCount += recursiveDeleteFileOrDirectory( file );
            }
            return removedCount;
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    int recursiveDeleteFileOrDirectory( string path ) {
        string p = makePreferred( path );
        if ( isDir( p ) ) {
            return recursiveDeleteDirectory( p );
        } else {
            bool deleted = deleteFileOrDirectory( p );
            if ( deleted )
                return 1;
            return 0;
        }
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

    void copyFileOrDirectory( string srcPath, string destDir, bool isOverwriteExisting, bool isRecursive ) {
        if ( isDir( srcPath ) ) {
            copyDir( srcPath, destDir, isOverwriteExisting, isRecursive );
        } else {
            copyFile( srcPath, destDir, isOverwriteExisting );
        }
    }

    void copyFile( string srcFile, string destDir, bool isOverwriteExisting ) {
        try {
            string destDir2 = addSeparatorToDirIfNeed( destDir );

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

    void copyDir( string srcDir, string destDir, bool isOverwriteExisting, bool isRecursive ) {
        try {
            string fsrcName = fileOrDirName( srcDir );

            string src = makePreferred( srcDir );
            string dest = makePreferred( concatPaths( destDir, fsrcName ) );

            if ( isOverwriteExisting && filesystem::exists( dest ) )
                filesystem::remove_all( dest );

            if ( isRecursive )
                filesystem::copy( src, dest, filesystem::copy_options::recursive );
            else filesystem::copy( src, dest );
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    void __copyFile( string file, string dest, string replacePath, bool isOverwriteExisting ) {
        string fname = strutil::replace( file, replacePath, "" );
        string dest2 = addSeparatorToDirIfNeed( dest );
        dest2 = dirPath( dest2 );
        dest2 = concatPaths( dest2, fname );

        createDirectories( dirPath( dest2 ) );

        if ( isOverwriteExisting && filesystem::exists( dest2 ) )
            filesystem::remove( dest2 );

        filesystem::copy_file( file, dest2 );
    }

    void copyFiles( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting ) {
        try {
            string src = makePreferred( srcDir );
            string dest = makePreferred( destDir );

            for( const auto& entry : filesystem::directory_iterator( src ) ) {
                string file = makePreferred( entry.path().string() );

                bool isCopyFile = true;
                if ( filter != nullptr )
                    isCopyFile = filter->isFilter( file );

                if ( isCopyFile && !filesystem::is_directory( file ) )
                    __copyFile( file, dest, replacePath, isOverwriteExisting );
            }
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    void recursiveCopyFiles( string srcDir, string destDir, string replacePath, FileFilter* filter, bool isOverwriteExisting ) {
        try {
            string src = makePreferred( srcDir );
            string dest = makePreferred( destDir );

            for( const auto& entry : filesystem::recursive_directory_iterator( src ) ) {
                string file = makePreferred( entry.path().string() );

                bool isCopyFile = true;
                if ( filter != nullptr )
                    isCopyFile = filter->isFilter( file );

                if ( isCopyFile && !filesystem::is_directory( file ) )
                    __copyFile( file, dest, replacePath, isOverwriteExisting );
            }
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

    bool fileExists( string path ) {
        return filesystem::exists( path );
    }

    string dirPath( string path ) {
        string p = makePreferred( path );

        size_t i = p.find_last_of( filesystem::path::preferred_separator );
        if ( i == string::npos )
            return p;
        return p.substr( 0, i+1 );
    }

    string recursiveDirPath( string path ) {
        string p = makePreferred( path );
        p = removeRecursiveJoker( p );
        return dirPath( p );
    }

    string recursiveDirPathToReplace( string path ) {
        string p = makePreferred( path );
        size_t i = p.find( "-" );
        if ( i == string::npos ) {
            return "";
        } else {
            if ( i == 0 ) {
                p = "";
            } else if ( i == 1 ) {
                p = "";
                p += filesystem::path::preferred_separator;
            } else {
                p = p.substr( 0, i );
            }
            return p;
        }
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

    string recursiveFileOrDirName( string path ) {
        string p = makePreferred( path );

        size_t i = p.find( "-" );
        if ( i == string::npos ) {
            return fileOrDirName( path );
        } else {
            i += 2;
            return p.substr( i, p.length()-i+1 );
        }
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

    string addSeparatorToDirIfNeed( string dir ) {
        string d = makePreferred( dir );
        if ( d.length() > 0 )
            if( d[ d.length()-1 ] != filesystem::path::preferred_separator )
                d += filesystem::path::preferred_separator;
        return d;
    }

    string parentDirPath( string path ) {
        string p = makePreferred( path );
        if ( p.length() > 0 ) {
            if ( p[ p.length()-1 ] == filesystem::path::preferred_separator )
                p = p.substr( 0, p.length()-1 );

            size_t i = p.find_last_of( filesystem::path::preferred_separator );
            if ( i != string::npos ) {
                size_t j = ( i == 0 ? string::npos : p.find_last_of( filesystem::path::preferred_separator, i-1 ) );
                if ( j == string::npos ) {
                    if ( filesystem::path::preferred_separator == '/' ) {
                        p = "/";
                    } else {
                        p = p.substr( 0, i );
                        p += filesystem::path::preferred_separator;
                    }
                } else {
                    p = p.substr( 0, i );
                }
            } else {
                p = "";
            }
        }
        return p;
    }

    string absolutePath( string path ) {
        filesystem::path p( path );
        if ( p.is_absolute() ) {
            return makePreferred( path );
        } else {
            string pp = currentPath();
            pp += filesystem::path::preferred_separator;
            pp += path;
            return makePreferred( pp );
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

    bool isJokerInPath( string path ) {
        string file = fileOrDirName( path );
        if ( file.length() > 0 )
            if ( file[ 0 ] == '*' )
                return true;
        return false;
    }

    string extension( string path ) {
        size_t i = path.find( '.' );
        if ( i == string::npos )
            return "";
        return path.substr( i+1, path.length()-i );
    }

    bool isDir( string path ) {
        return filesystem::is_directory( path );
    }

    bool isEmptyDir( string dir ) {
        return filesystem::is_empty( dir );
    }

    string removeRecursiveJoker( string path ) {
        string p = makePreferred( path );
        string replaceStr = "-";
        replaceStr += filesystem::path::preferred_separator;
        return strutil::replace( p, replaceStr, "" );
    }

    string removeDirContentJoker( string path ) {
        string p = makePreferred( path );
        if ( p.length() > 0 )
            if ( p[ p.length()-1 ] == '*' )
                return p.substr( 0, p.length()-2 );
        return p;
    }

}
