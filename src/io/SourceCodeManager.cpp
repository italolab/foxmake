
#include "SourceCodeManager.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>
#include <fstream>

using std::ifstream;
using std::getline;

#include <iostream>
using namespace std;

SourceCodeManager::SourceCodeManager() {
    this->filesToCompileManager = new FilesToCompileManager();
}

bool SourceCodeManager::recursiveProcFiles( string basedir ) {
    scInfosMap.clear();
    dependenciesMap.clear();
    allSourceCodeFiles.clear();

    string prefBaseDir = io::makePreferred( basedir );
    try {
        for( const auto& entry : filesystem::recursive_directory_iterator( prefBaseDir ) ) {
            string filePath = io::relativePath( entry.path().string() );
            filePath = io::makePreferred( filePath );
            if ( !filesystem::is_directory( filePath ) ) {
                if ( strutil::endsWith( filePath, ".cpp" ) || strutil::endsWith( filePath, ".c" ) ) {
                    string objFilePath = strutil::replace( filePath, ".cpp", ".o" );
                    objFilePath = strutil::replace( objFilePath, ".c", ".o" );

                    SourceCodeInfo* info = new SourceCodeInfo;
                    info->filePath = filePath;
                    info->objFilePath = objFilePath;
                    scInfosMap[ filePath ] = info;
                } else if ( strutil::endsWith( filePath, ".h" ) ) {
                    vector<string> dependencies;
                    dependenciesMap[ filePath ] = dependencies;
                }
                allSourceCodeFiles.push_back( filePath );
            }
        }

        this->loadDependencies();

        /*
        for( const auto& pair : dependenciesMap ) {
            cout << pair.first << endl;
            for( string path : pair.second )
                cout << "\t" << path << endl;
        }
        */

        return true;
    } catch ( const filesystem::filesystem_error& error ) {
        return false;
    }
}

bool SourceCodeManager::loadDependencies() {
    for( const auto& pair : dependenciesMap )
        ((vector<string>)pair.second).clear();

    for( const auto& pair : dependenciesMap ) {
        bool ok = this->loadDepencenciesForHeaderFile( pair.first );
        if ( !ok )
            return false;

        string cpp = strutil::replace( pair.first, ".h", ".cpp" );
        this->loadDepencenciesForHeaderFile( cpp );
    }

    return true;
}

bool SourceCodeManager::loadDepencenciesForHeaderFile( string headerFilePath ) {
    ifstream in( headerFilePath );
    if ( !in.is_open() )
        return false;

    bool isEnd = false;

    string line;
    while( !isEnd && !in.eof() ) {
        getline( in, line );
        line = strutil::removeStartWhiteSpaces( line );

        size_t i = line.find( '{' );
        if ( i != string::npos ) {
            isEnd = true;
        } else {
            if ( strutil::startsWith( line, "#include" ) ) {
                size_t j = line.find( '\"' );
                while( j != string::npos ) {
                    j++;

                    size_t k = line.find( '\"', j );
                    if ( k != string::npos ) {
                        string includePath = line.substr( j, k-j );

                        string dir = io::dirPath( headerFilePath );
                        includePath = io::resolvePath( dir, includePath );

                        string cppPath = strutil::replace( headerFilePath, ".h", ".cpp" );
                        if ( io::fileExists( cppPath ) )
                            if ( scInfosMap.find( cppPath ) != scInfosMap.end() )
                                dependenciesMap[ includePath ].push_back( cppPath );
                    }

                    j = line.find( '\"', k+1 );
                }
            }
        }
    }

    in.close();
    return true;
}

SourceCodeInfo* SourceCodeManager::getSourceCodeInfo( string filePath ) {
    return scInfosMap[ filePath ];
}

vector<string> SourceCodeManager::sourceCodeFilePaths() {
    vector<string> paths;
    for( const auto& pair : scInfosMap )
        paths.push_back( pair.first );
    return paths;
}

bool SourceCodeManager::isHeaderFileLoaded( string filePath ) {
    return dependenciesMap.find( filePath ) != dependenciesMap.end();
}

vector<string>& SourceCodeManager::getDepencenciesForHeaderFile( string filePath ) {
    return dependenciesMap[ filePath ];
}

void SourceCodeManager::loadFilesToCompile( vector<string>& filesToCompile, string configFilePath ) {
    filesToCompileManager->loadFilesToCompile( filesToCompile, allSourceCodeFiles, dependenciesMap, configFilePath );
}
