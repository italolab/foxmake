

#include "io.h"
#include "../util/strutil.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

io_error::io_error( string msg ) : runtime_error( msg ) {}
joker_error::joker_error( string msg ) : io_error( msg ) {}

namespace io {

    void copyFileOrDirectory( string path, string dir, bool isOverwriteExisting ) {
        if ( isDirectory( path ) ) {
            copyDir( path, dir, isOverwriteExisting );
        } else {
            copyFile( path, dir, isOverwriteExisting );
        }
    }

    void deleteFileOrDirectory( string path ) {
        if ( isDirectory( path ) ) {
            deleteDirectory( path );
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
                if ( !filesystem::is_directory( file ) && strutil::endsWith( file, ext ) ) {
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

    int recursiveDeleteFiles( string dir ) {
        int removedCount = 0;
        try {
            string dirpath = makePreferred( dir );
            for( const auto& entry : filesystem::recursive_directory_iterator( dirpath ) ) {
                string file = makePreferred( entry.path().string() );
                if ( filesystem::is_directory( file ) ) {
                    removedCount += deleteDirectory( file );
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

    int deleteDirectory( string path ) {
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

    void copyDir( string srcDir, string destDir, bool isOverwriteExisting ) {
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

    void __copyFile( string file, string dest, string srcFile, bool isOverwriteExisting ) {
        bool isCopy;
        if ( isJokerCopyInPath( srcFile ) ) {
            string ext = extension( srcFile );
            if ( ext == "" ) {
                isCopy = !filesystem::is_directory( file );
            } else {
                isCopy = strutil::endsWith( file, ext );
            }
        } else {
            isCopy = !filesystem::is_directory( file );
        }

        if ( isCopy ) {
            string dest2 = addSeparatorToDirIfNeed( dest );
            dest2 = baseDirPath( dest2 );

            string baseDir = baseDirPath( srcFile );
            baseDir = addSeparatorToDirIfNeed( baseDir );

            string fname = strutil::replace( file, baseDir, "" );

            dest2 = concatPaths( dest2, fname );

            createDirectories( dirPath( dest2 ) );

            if ( isOverwriteExisting && filesystem::exists( dest2 ) )
                filesystem::remove( dest2 );

            filesystem::copy_file( file, dest2 );
        }
    }

    void copyFiles( string srcPath, string destDir, bool isOverwriteExisting ) {
        try {
            string src = makePreferred( srcPath );
            string dest = makePreferred( destDir );

            string srcDir = baseDirPath( src );

            for( const auto& entry : filesystem::directory_iterator( srcDir ) ) {
                string file = makePreferred( entry.path().string() );
                __copyFile( file, dest, src, isOverwriteExisting );
            }
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    void recursiveCopyFiles( string srcPath, string destDir, bool isOverwriteExisting ) {

        try {
            string src = makePreferred( srcPath );
            string dest = makePreferred( destDir );

            string srcDir = src;
            if ( strutil::startsWith( srcPath, "**" ) ) {
                size_t i = 3;
                size_t j = srcPath.find( filesystem::path::preferred_separator, i );

            }

            for( const auto& entry : filesystem::recursive_directory_iterator( srcDir ) ) {
                string file = makePreferred( entry.path().string() );
                __copyFile( file, dest, src, isOverwriteExisting );
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

    string baseDirPath( string path ) {
        string p = makePreferred( path );
        size_t i = p.find( "**" );
        if ( i == string::npos ) {
            return dirPath( p );
        } else {
            if ( i == 0 ) {
                p = "." + filesystem::path::preferred_separator;
            } else if ( i == 1 ) {
                p = "" + filesystem::path::preferred_separator;
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

    string baseFileOrDirName( string path ) {
        string p = makePreferred( path );

        size_t i = p.find( "**" );
        if ( i == string::npos ) {
            return fileOrDirName( path );
        } else {
            i += 3;
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
        string d = dir;
        if ( d.length() > 0 )
            if( d[ d.length()-1 ] != filesystem::path::preferred_separator )
                d += filesystem::path::preferred_separator;
        return d;
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

    bool isJokerCopyInPath( string path ) {
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

    bool isDirectory( string path ) {
        return filesystem::is_directory( path );
    }

}
