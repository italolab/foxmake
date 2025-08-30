
#include "FilesToCompileManager.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>
#include <fstream>

namespace filesystem = std::filesystem;

FilesToCompileManager::FilesToCompileManager( string sourceFileExtensions, string headerFileExtensions ) {
    this->sourceFileExtensions = sourceFileExtensions;
    this->headerFileExtensions = headerFileExtensions;
}

void FilesToCompileManager::loadFilesToCompile(
                                    vector<CodeInfo*>& filesToCompile,
                                    map<string, CodeInfo*>& allSourceInfosMap,
                                    string configFilePath ) {

    map<string, long> timesElapsedMap;

    if ( io::fileExists( configFilePath ) )
        this->loadLastWriteTimesFromFile( timesElapsedMap, configFilePath );

    for( const auto& pair : allSourceInfosMap ) {
        string filePath = pair.second->filePath;

        if ( !filesystem::is_directory( filePath ) ) {
            if ( timesElapsedMap.find( filePath ) != timesElapsedMap.end() ) {
                long savedWritingTimeElapsed = timesElapsedMap[ filePath ];

                long currentWritingTimeElapsed = io::lastWriteTime( filePath );
                if ( currentWritingTimeElapsed > savedWritingTimeElapsed )
                    this->addDependenciesToCompile( filesToCompile, allSourceInfosMap, filePath );                
            } else {
                this->addDependenciesToCompile( filesToCompile, allSourceInfosMap, filePath );
            }
        }
    }

    this->removeHeaderFiles( filesToCompile );
}

void FilesToCompileManager::addDependenciesToCompile(
                                    vector<CodeInfo*>& filesToCompile,
                                    map<string, CodeInfo*>& allSourceInfosMap,
                                    string filePath ) {

    if ( strutil::endsWithSome( filePath, headerFileExtensions ) ) {
        recursiveLoadDependencies( filesToCompile, allSourceInfosMap, filePath );
    } else if ( strutil::endsWithSome( filePath, sourceFileExtensions ) ) {
        if ( !containsToCompileFile( filesToCompile, filePath ) ) {
            CodeInfo* info = allSourceInfosMap[ filePath ];
            filesToCompile.push_back( info );
        }
    }
}

void FilesToCompileManager::recursiveLoadDependencies(
                                        vector<CodeInfo*>& filesToCompile,
                                        map<string, CodeInfo*>& allSourceInfosMap,
                                        string filePath ) {

    if ( allSourceInfosMap.find( filePath ) == allSourceInfosMap.end() )
        return;

    filesToCompile.push_back( allSourceInfosMap[ filePath ] );
                    
    vector<string>& deps = allSourceInfosMap[ filePath ]->dependencies;
    for( string fpath : deps ) {
        if ( !this->containsToCompileFile( filesToCompile, fpath ) )
            this->recursiveLoadDependencies( filesToCompile, allSourceInfosMap, fpath );
    }
}

bool FilesToCompileManager::containsToCompileFile( vector<CodeInfo*>& filesToCompile, string filePath ) {
    for( CodeInfo* info : filesToCompile )
        if ( info->filePath == filePath )
            return true;
    return false;
}

void FilesToCompileManager::removeHeaderFiles( vector<CodeInfo*>& filesToCompile ) {
    int len = filesToCompile.size();
    for( int i = 0; i < len; i++ ) {
        string fileName = filesToCompile[ i ]->filePath;
        if ( strutil::endsWithSome( fileName, headerFileExtensions ) ) {
            filesToCompile.erase( filesToCompile.begin() + i );
            i--;
            len--;
        }
    }
}

bool FilesToCompileManager::loadLastWriteTimesFromFile( map<string, long>& writingTimesElapsedMap, string configFilePath ) {
    ifstream in( configFilePath );
    if ( !in.is_open() )
        return false;

    while( !in.eof() ) {
        string line;
        getline( in, line );

        size_t i = line.find( '=' );
        if ( i != string::npos ) {
            string filePath = line.substr( 0, i );
            string lastWriteTime = line.substr( i+1, line.length()-i+2 );

            writingTimesElapsedMap[ filePath ] = std::stol( lastWriteTime );
        }
    }

    in.close();
    return true;
}

bool FilesToCompileManager::saveLastWriteTimesInFile( map<string, CodeInfo*>& allSourceInfosMap, string configFileName ) {
    ofstream out( configFileName );
    if ( !out.is_open() )
        return false;

    for( const auto& pair : allSourceInfosMap ) {
        string filePath = pair.second->filePath;

        long lastWriteTime = io::lastWriteTime( filePath );
        out << filePath << "=" << lastWriteTime << "\n";
    }

    out.close();
    return true;
}
