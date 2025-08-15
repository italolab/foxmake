
#include "FilesToCompileManager.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>
#include <fstream>

namespace filesystem = std::filesystem;

void FilesToCompileManager::loadFilesToCompile(
                                    vector<string>& filesToCompile,
                                    map<string, SourceCodeInfo*>& allSourceInfosMap,
                                    string configFilePath ) {

    map<string, long> timesElapsedMap;

    if ( io::fileExists( configFilePath ) )
        this->loadWritingTimesElapsedFile( timesElapsedMap, configFilePath );

    for( const auto& pair : allSourceInfosMap ) {
        string filePath = pair.second->filePath;

        if ( !filesystem::is_directory( filePath ) ) {
            if ( timesElapsedMap.find( filePath ) != timesElapsedMap.end() ) {
                long savedWritingTimeElapsed = timesElapsedMap[ filePath ];

                long currentWritingTimeElapsed = io::writingTimeElapsedInMS( filePath );
                if ( currentWritingTimeElapsed < savedWritingTimeElapsed )
                    this->addDependenciesToCompile( filesToCompile, allSourceInfosMap, filePath );
            } else {
                this->addDependenciesToCompile( filesToCompile, allSourceInfosMap, filePath );
            }
        }
    }

    this->saveWritingTimesElapsedInFile( allSourceInfosMap, configFilePath );
}

void FilesToCompileManager::addDependenciesToCompile(
                                    vector<string>& filesToCompile,
                                    map<string, SourceCodeInfo*>& allSourceInfos,
                                    string filePath ) {

    if ( strutil::endsWith( filePath, ".h" ) ) {
        recursiveLoadDependencies( filesToCompile, allSourceInfos, filePath );
    } else if ( strutil::endsWith( filePath, ".cpp" ) || strutil::endsWith( filePath, ".c" ) ) {
        if ( !containsInVector( filesToCompile, filePath ) )
            filesToCompile.push_back( filePath );
    }
}

void FilesToCompileManager::recursiveLoadDependencies(
                                        vector<string>& filesToCompile,
                                        map<string, SourceCodeInfo*>& allSourceInfosMap,
                                        string filePath ) {

    if ( !this->containsInVector( filesToCompile, filePath ) )
        filesToCompile.push_back( filePath );

    if ( allSourceInfosMap.find( filePath ) != allSourceInfosMap.end() ) {
        vector<string>& deps = allSourceInfosMap[ filePath ]->dependencies;
        for( string fpath : deps ) {
            if ( !this->containsInVector( filesToCompile, fpath ) )
                this->recursiveLoadDependencies( filesToCompile, allSourceInfosMap, fpath );
        }
    }

}

bool FilesToCompileManager::containsInVector( vector<string>& filesToCompile, string filePath ) {
    for( string path : filesToCompile )
        if ( path == filePath )
            return true;
    return false;
}

bool FilesToCompileManager::loadWritingTimesElapsedFile( map<string, long>& writingTimesElapsedMap, string configFilePath ) {
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

bool FilesToCompileManager::saveWritingTimesElapsedInFile( map<string, SourceCodeInfo*>& allSourceInfosMap, string configFileName ) {
    ofstream out( configFileName );
    if ( !out.is_open() )
        return false;

    for( const auto& pair : allSourceInfosMap ) {
        string filePath = pair.second->filePath;

        long lastWriteTime = io::writingTimeElapsedInMS( filePath );
        out << filePath << "=" << lastWriteTime << "\n";
    }

    out.close();
    return true;
}
