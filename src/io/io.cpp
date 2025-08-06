

#include "io.h"
#include "../util/strutil.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

io_error::io_error( string msg ) : runtime_error( msg ) {

}

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

    int deleteFilesByExt( string dir, string ext ) {
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

    int deleteFiles( string dir ) {
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

    void copyFilesByExt( string srcDir, string ext, string destDir, bool isOverwriteExisting ) {
        try {
            string src = makePreferred( srcDir );
            string dest = makePreferred( destDir );

            for( const auto& entry : filesystem::recursive_directory_iterator( src ) ) {
                string file = makePreferred( entry.path().string() );

                if ( strutil::endsWith( file, ext ) ) {
                    string dest2 = addSeparatorToDirIfNeed( dest );
                    dest2 = concatPaths( dest2, file );

                    if ( isOverwriteExisting )
                        if ( filesystem::exists( dest2 ) )
                            filesystem::remove( dest2 );

                    createDirectories( directoryPath( dest2 ) );
                    filesystem::copy_file( file, dest2 );
                }
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

    string directoryPath( string path ) {
        bool recursive;
        return directoryPath( path, recursive );
    }

    string directoryPath( string path, bool& recursive ) {
        string p = makePreferred( path );
        size_t i = p.find_last_of( filesystem::path::preferred_separator );
        if ( i == string::npos )
            return p;
        string dir = p.substr( 0, i+1 );

        recursive = false;
        if ( i > 3 ) {
            if ( dir[ i-1 ] == '*' && dir[ i-2 ] == '*' && dir[ i-3 ] == filesystem::path::preferred_separator ) {
                dir = dir.substr( 0, i-3 );
                recursive = true;
            }
        }
        return dir;
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

    bool isDirectory( string path ) {
        return filesystem::is_directory( path );
    }

}
