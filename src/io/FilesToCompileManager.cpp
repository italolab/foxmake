
#include "FilesToCompileManager.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>
#include <fstream>

#include <iostream>
using namespace std;

namespace filesystem = std::filesystem;

void FilesToCompileManager::loadFilesToCompile(
                                    vector<string>& filesToCompile,
                                    vector<string>& sourceFiles,
                                    map<string, vector<string>>& dependenciesMap,
                                    string configFilePath ) {

    map<string, long> timesElapsedMap;

    if ( io::fileExists( configFilePath ) )
        this->loadWritingTimesElapsedFile( timesElapsedMap, configFilePath );

    for( string filePath : sourceFiles ) {
        if ( !filesystem::is_directory( filePath ) ) {
            if ( timesElapsedMap.find( filePath ) != timesElapsedMap.end() ) {
                long savedWritingTimeElapsed = timesElapsedMap[ filePath ];

                long currentWritingTimeElapsed = io::writingTimeElapsedInMS( filePath );
                if ( currentWritingTimeElapsed < savedWritingTimeElapsed )
                    this->addDependenciesToCompile( filesToCompile, dependenciesMap, filePath );
            } else {
                this->addDependenciesToCompile( filesToCompile, dependenciesMap, filePath );
            }
        }
    }

    this->saveWritingTimesElapsedInFile( sourceFiles, configFilePath );
}

void FilesToCompileManager::addDependenciesToCompile(
                                    vector<string>& filesToCompile,
                                    map<string, vector<string>>& dependenciesMap,
                                    string filePath ) {

    if ( strutil::endsWith( filePath, ".h" ) ) {
        recursiveLoadDependencies( filesToCompile, dependenciesMap, filePath );
    } else if ( strutil::endsWith( filePath, ".cpp" ) || strutil::endsWith( filePath, ".c" ) ) {
        if ( !containsInVector( filesToCompile, filePath ) )
            filesToCompile.push_back( filePath );
    }
}

void FilesToCompileManager::recursiveLoadDependencies(
                                        vector<string>& filesToCompile,
                                        map<string, vector<string>>& depsMap,
                                        string headerFilePath ) {

    string filePath = strutil::replace( headerFilePath, ".h", ".cpp" );
    if ( io::fileExists( filePath ) ) {
        if ( !this->containsInVector( filesToCompile, filePath ) )
            filesToCompile.push_back( filePath );
    } else {
        filePath = strutil::replace( headerFilePath, ".h", ".c" );
        if ( io::fileExists( filePath ) )
            if ( !this->containsInVector( filesToCompile, filePath ) )
                filesToCompile.push_back( filePath );
    }

    cout << headerFilePath << endl;
    if ( depsMap.find( headerFilePath ) != depsMap.end() ) {
        vector<string>& deps = depsMap[ headerFilePath ];
        for( string fpath : deps ) {
            string headerPath = strutil::replace( fpath, ".cpp", ".h" );
            cout << "\t" << headerPath << endl;
            if ( !this->containsInVector( filesToCompile, fpath ) )
                this->recursiveLoadDependencies( filesToCompile, depsMap, headerPath );
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

bool FilesToCompileManager::saveWritingTimesElapsedInFile( vector<string>& sourceFiles, string configFileName ) {
    ofstream out( configFileName );
    if ( !out.is_open() )
        return false;

    for( string filePath : sourceFiles ) {
        long lastWriteTime = io::writingTimeElapsedInMS( filePath );

        out << filePath << "=" << lastWriteTime << "\n";
    }

    out.close();
    return true;
}
