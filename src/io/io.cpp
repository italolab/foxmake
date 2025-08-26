
#include "io.h"
#include "../util/strutil.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include <sys/stat.h>

using std::stringstream;

namespace filesystem = std::filesystem;

io_error::io_error( string msg ) : runtime_error( msg ) {}
joker_error::joker_error( string msg ) : io_error( msg ) {}

namespace io {

    ByNameFileFilter* by_name_file_filter( string file ) {
        return new ByNameFileFilter( file );
    }

    void writeInTextFile( string file, string text ) {
        ofstream ofs( file );

        ofs << text;
        ofs.close();
    }

    string readFromTextFile( string file ) {
        ifstream ifs( file );

        stringstream ss;
        if ( ifs.is_open() ) {
            string line;
            while( getline( ifs, line, '\n' ) )
                ss << line << "\n";
        }
        
        return ss.str();
    }

    int recursiveCountFilesInDir( string dir ) {
        try {
            string dirpath = makePreferred( dir );
            int count = 0;
            for( const auto& entry : filesystem::recursive_directory_iterator( dirpath ) ) {
                string file = entry.path().string();
                if ( !filesystem::is_directory( file ) )
                    count++;            
            }
            return count;
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    bool deleteFileOrDirectory( string path ) {
        string p = makePreferred( path );
        try {
            return filesystem::remove( p );
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    int deleteFiles( string dir, FileFilter* filter ) {
        int removedCount = 0;
        try {
            string dirpath = makePreferred( dir );
            for( const auto& entry : filesystem::directory_iterator( dirpath ) ) {
                string file = makePreferred( entry.path().string() );

                if ( filter != nullptr )
                    if ( !filter->match( file ) )
                        continue;
                
                removedCount += recursiveDeleteFileOrDirectory( file );
            }            
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
        return removedCount;
    }

    int recursiveDeleteFiles( string dir, FileFilter* filter ) {
        int removedCount = 0;
        try {
            string dirpath = makePreferred( dir );
            for( const auto& entry : filesystem::directory_iterator( dirpath ) ) {
                string file = makePreferred( entry.path().string() );

                if ( filesystem::is_directory( file ) )
                    removedCount += recursiveDeleteFiles( file, filter );                

                if ( filter != nullptr )
                    if ( !filter->match( file ) )
                        continue;

                removedCount += recursiveDeleteFileOrDirectory( file );                                
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

            filesystem::path dest = makePreferred( destDir2 + fname );

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
            string dest = makePreferred( destDir );

            dest = addSeparatorToDirIfNeed( dest );
            dest += fsrcName;

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
        dest2 = dest2 + fname;

        createDirs( dirPath( dest2 ) );

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
                    isCopyFile = filter->match( file );

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
                    isCopyFile = filter->match( file );

                if ( isCopyFile && !filesystem::is_directory( file ) )
                    __copyFile( file, dest, replacePath, isOverwriteExisting );
            }
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    bool createDir( string path ) {
        string p = makePreferred( path );
        try {
            return filesystem::create_directory( p );
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    bool createDirs( string path ) {
        string p = makePreferred( path );
        try {
            return filesystem::create_directories( p );
        } catch ( const filesystem::filesystem_error& e ) {
            throw io_error( e.what() );
        }
    }

    bool fileExists( string path ) {
        return filesystem::exists( path );
    }

    string dirPath( string path ) {
        string p = makePreferred( path );

        size_t i = p.find_last_of( filesystem::path::preferred_separator );
        if ( i == string::npos ) {
            if ( filesystem::is_directory( path ) )
                return p;
            return "";
        }
        return p.substr( 0, i+1 );
    }

    string recursiveDirPath( string path ) {
        string p = makePreferred( path );
        p = removeRecursiveJoker( p );
        return dirPath( p );
    }

    string recursiveDirPathToReplace( string path ) {
        string p = makePreferred( path );
        size_t i = p.find( "**" );
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

        if ( p.length() > 0 ) {
            if ( p[ p.length()-1 ] == filesystem::path::preferred_separator ) {
                size_t j = p.find_last_of( filesystem::path::preferred_separator, i-1 );
                size_t k = ( j == string::npos ? 0 : j+1 );
                return p.substr( k, p.length()-k-1 );
            }
        }

        return p.substr( i+1, p.length()-i );
    }

    string fileOrDirNameWithoutExtension( string pathOrName ) {
        string name = fileOrDirName( makePreferred( pathOrName ) );

        size_t i = name.find( '.' );
        if ( i == string::npos )
            return name;
        return name.substr( 0, i );
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

    string parentPath( string path ) {
        string p = makePreferred( path );
        if ( p.length() > 0 ) {
            if ( p[ p.length()-1 ] == filesystem::path::preferred_separator )
                p = p.substr( 0, p.length()-1 );

            size_t i = p.find_last_of( filesystem::path::preferred_separator );
            if ( i != string::npos ) {                
                if ( i == 0 ) {
                    p = "/";
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
        if ( path == "." )
            return currentPath();

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string path2 = path;
        if ( strutil::startsWith( path2, "."+sep ) )
            path2 = path2.substr( 2, path2.length()-2 );
            
        filesystem::path p( path2 );
        if ( p.is_absolute() ) {
            return makePreferred( path2 );
        } else {
            string pp = currentPath();
            pp = addSeparatorToDirIfNeed( pp );
            pp += path2;
            return makePreferred( pp );
        }
    }

    string relativePath( string path ) {
        if ( path == "." )
            return "";

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string path2 = path;
        if ( strutil::startsWith( path2, "."+sep ) )
            path2 = path2.substr( 2, path2.length()-2 );

        filesystem::path p( path2 );
        if ( p.is_absolute() ) {
            return filesystem::relative( path2, currentPath() ).string();
        } else {
            return makePreferred( path2 );
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
        string name = fileOrDirName( path );
        size_t i = name.find( '.' );
        if ( i == string::npos )
            return "";
        return name.substr( i+1, name.length()-i );
    }

    bool isDir( string path ) {
        return filesystem::is_directory( path );
    }

    bool isEmptyDir( string dir ) {
        return filesystem::is_empty( dir );
    }

    string removeRecursiveJoker( string path ) {
        string p = makePreferred( path );
        string replaceStr = "**";
        replaceStr += filesystem::path::preferred_separator;
        return strutil::replace( p, replaceStr, "" );
    }

    void countTwoDotsAndSlash( string path, int index, size_t& count, size_t& i, size_t& j, size_t& k ) {
        string sep = "";
        sep += filesystem::path::preferred_separator;

        string rpath = path.substr( index, path.length()-index );
        rpath = makePreferred( rpath );

        size_t len = rpath.length();

        if ( rpath == ".." ) {
            k = 2;
            i = index;
            j = index+2;
            count = 1;
        } else {
            i = rpath.find( ".."+sep, index );
            j = ( i != string::npos ? i : index );
            k = ( i != string::npos ? i : index );
            count = 0;
            bool isContinue = i != string::npos;
            while( isContinue ) {
                count++;
                j = k+3;
                k += 3;
                if ( k+2 < len ) {
                    isContinue = rpath[ k ] == '.';
                    isContinue &= rpath[ k+1 ] == '.';
                    isContinue &= rpath[ k+2 ] == filesystem::path::preferred_separator;
                } else {
                    isContinue = false;
                }
            }
        }
    }

    string removeInitTwoDotsAndSlash( string relativePath ) {
        if ( relativePath == "." )
            return "";

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string rpath = makePreferred( relativePath );
        if ( strutil::startsWith( rpath, "."+sep ) )
            rpath = strutil::replace( rpath, "."+sep, "" );
        
        size_t count, i, j, k;    
        countTwoDotsAndSlash( rpath, 0, count, i, j, k );
        return rpath.substr( k, rpath.length()-k );
    }

    string absoluteResolvePath( string path ) {
        return resolvePath( absolutePath( path ) );
    }

    string resolvePath( string path ) {
        if ( path == "." )
            return "";

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string rpath = makePreferred( path );
        if ( strutil::startsWith( rpath, "."+sep ) )
            rpath = strutil::replace( rpath, "."+sep, "" );

        size_t count, i, j, k;
        countTwoDotsAndSlash( rpath, 0, count, i, j, k );

        if( count == 0 )
            return rpath;
        
        string basePath = rpath.substr( 0, i );
        string relativePath = rpath.substr( i, rpath.length()-i ).replace( 0, j-i, "" );

        for( size_t l = 0; l < count; l++ )
            basePath = parentPath( basePath );        
        basePath = addSeparatorToDirIfNeed( basePath );
        
        return basePath + relativePath;
    }

    string resolvePath( string currDir, string path ) {
        string sep = "";
        sep += filesystem::path::preferred_separator;

        string resolvedPath = makePreferred( path );
        if ( strutil::startsWith( resolvedPath, "."+sep ) )
            resolvedPath = strutil::replace( resolvedPath, "."+sep, "" );

        size_t i = resolvedPath.find( ".."+sep );
        bool isRepeat = i != string::npos;
        string dir = addSeparatorToDirIfNeed( currDir );
        while( isRepeat ) {
            dir = parentPath( dir );
            dir = addSeparatorToDirIfNeed( dir );

            size_t j = resolvedPath.find( ".."+sep, i+3 );
            if ( j == string::npos ) {
                isRepeat = false;
            } else {
                i = j;
            }
        }

        size_t k = ( i == string::npos ? 0 : i+3 );
        return resolvedPath.replace( 0, k, dir );
    }

    long lastWriteTime( string path ) {
        struct stat fileStat;
        int result = stat( path.c_str(), &fileStat );
        if ( result != 0 )
            return -1;

        return fileStat.st_mtime;
    }

}
