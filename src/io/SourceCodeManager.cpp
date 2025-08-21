
#include "SourceCodeManager.h"
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>


#include <iostream>
using namespace std;

using std::getline;

SourceCodeManager::SourceCodeManager( string sourceFileExtensions, string headerFileExtensions ) {
    this->filesToCompileManager = new FilesToCompileManager( sourceFileExtensions, headerFileExtensions );
    this->sourceFileExtensions = sourceFileExtensions;
    this->headerFileExtensions = headerFileExtensions;
}

SourceCodeManager::~SourceCodeManager() {
    delete filesToCompileManager;
    for( const auto& pair : allCodeInfosMap )
        delete pair.second;
}

bool SourceCodeManager::recursiveProcFiles( string basedir ) {
    sourceCodeInfosMap.clear();
    allCodeInfosMap.clear();
    classToIncludeMap.clear();

    string prefBaseDir = io::makePreferred( basedir );
    try {
        for( const auto& entry : filesystem::recursive_directory_iterator( prefBaseDir ) ) {
            string filePath = io::relativePath( entry.path().string() );
            filePath = io::makePreferred( filePath );
            if ( !filesystem::is_directory( filePath ) ) {
                string ext = io::extension( filePath );
                string objFilePath = strutil::replace( filePath, ext, "o" );

                vector<string> dependencies;
                vector<string> extendedClasses;

                CodeInfo* info = new CodeInfo;
                info->filePath = filePath;
                info->objFilePath = objFilePath;
                info->dependencies = dependencies;
                info->extendedClasses = extendedClasses;

                if ( strutil::endsWithSome( filePath, sourceFileExtensions ) ) {
                    sourceCodeInfosMap[ filePath ] = info;
                    allCodeInfosMap[ filePath ] = info;
                } else if ( strutil::endsWithSome( filePath, headerFileExtensions ) ) {
                    allCodeInfosMap[ filePath ] = info;
                }
            }
        }

        return this->loadDependencies();
    } catch ( const filesystem::filesystem_error& error ) {
        return false;
    }
}

bool SourceCodeManager::loadDependencies() {
    for( const auto& pair : allCodeInfosMap )
        ((CodeInfo*)pair.second)->dependencies.clear();

    for( const auto& pair : allCodeInfosMap ) {
        CodeInfo* info = pair.second;
        bool ok = this->loadDepencenciesForFile( info->filePath );
        if ( !ok )
            return false;        
    }

    for( const auto& pair : allCodeInfosMap ) {
        CodeInfo* info = pair.second;
        vector<string> extendedClasses = info->extendedClasses;
        for( string exClass : extendedClasses )
            if ( classToIncludeMap.find( exClass ) != classToIncludeMap.end() )
                info->dependencies.push_back( classToIncludeMap[ exClass ] );
    }

    return true;
}

bool SourceCodeManager::loadDepencenciesForFile( string filePath ) {
    ifstream in( filePath );
    if ( !in.is_open() )
        return false;

    string line;
    while( !in.eof() ) {
        getline( in, line );
        line = strutil::removeStartWhiteSpaces( line );

        bool interpreted = this->interpretsInclude( line, filePath );
        if ( !interpreted )
            interpreted = this->interpretsClasse( in, line, filePath );
    }

    in.close();
    return true;
}

bool SourceCodeManager::interpretsInclude( string line, string filePath ) {
    if ( !strutil::startsWith( line, "#include" ) )
        return false;

    size_t j = line.find( '\"' );
    while( j != string::npos ) {
        j++;

        size_t k = line.find( '\"', j );
        if ( k != string::npos ) {
            string includePath = line.substr( j, k-j );

            string dir = io::dirPath( filePath );
            includePath = io::resolvePath( dir, includePath );

            cout << includePath << endl;

            if ( allCodeInfosMap.find( includePath ) != allCodeInfosMap.end() )
                allCodeInfosMap[ includePath ]->dependencies.push_back( filePath );
        }

        j = line.find( '\"', k+1 );
    }

    return true;
}

bool SourceCodeManager::interpretsClasse( ifstream& in, string line, string filePath ) {
    size_t i = 0;
    size_t j = 0;

    size_t k = line.find( "\"" );
    if ( k != string::npos )
        return false;

    if ( strutil::startsWith( line, "class" ) ) {
        i = 0;
        j = 6;
    } else {
        i = line.find( " class " );
        if ( i == string::npos )
            return false;

        j = 7;
    }

    i += j;

    string line2 = line;

    char ch = '\0';
    if ( i < line2.length() )
        ch = line2[ i ];

    size_t len = line2.length();

    stringstream ss;
    while( !strutil::isWhiteSpace( ch ) && ch != ':' && ch != '{' && i < len ) {
        ss << ch;
        i++;
        if ( i < len )
            ch = line2[ i ];
    }

    string className = ss.str();
    if ( className.length() > 0 )
        classToIncludeMap[ className ] = filePath;

    while ( ch != ':' && ch != '{' && i < len ) {
        i++;
        if ( i < len )
            ch = line2[ i ];
    }

    if ( ch == ':' ) {
        i++;
        while( ch != '{' && !in.eof() ) {
            size_t len = line2.length();
            while( ch != '{' && i < len ) {
                ch = line2[ i ];
                while( strutil::isWhiteSpace( ch ) && i < len ) {
                    i++;
                    if ( i < len )
                        ch = line2[ i ];
                }

                if ( ch == ',' ) {
                    i++;
                    continue;
                }

                if ( ch == '{' ) {
                    i = len;
                    continue;
                }

                if ( strutil::isNextToken( line2, i, "public" ) ) {
                    i += 7;
                } else if ( strutil::isNextToken( line2, i, "protected" ) ) {
                    i += 10;
                } else if ( strutil::isNextToken( line2, i, "private" ) ) {
                    i += 8;
                }

                if ( i < len )
                    ch = line2[ i ];

                stringstream ss;
                while( !strutil::isWhiteSpace( ch ) && ch != ',' && ch != '{' && i < len ) {
                    ss << ch;
                    i++;
                    if ( i < len )
                        ch = line2[ i ];
                }

                string extendedClassName = ss.str();
                if ( extendedClassName.length() > 0 )
                    allCodeInfosMap[ filePath ]->extendedClasses.push_back( extendedClassName );
            }

            if ( i == len && ch != '{' && !in.eof() ) {
                getline( in, line2 );
                i = 0;
            }
        }

        return true;
    }

    return false;
}


CodeInfo* SourceCodeManager::getSourceCodeInfo( string filePath ) {
    return sourceCodeInfosMap[ filePath ];
}

vector<string> SourceCodeManager::sourceFilePaths() {
    vector<string> paths;
    for( const auto& pair : sourceCodeInfosMap )
        paths.push_back( pair.first );
    return paths;
}

vector<CodeInfo*> SourceCodeManager::sourceCodeInfos() {
    vector<CodeInfo*> infos;
    for( const auto& pair : sourceCodeInfosMap )
        infos.push_back( pair.second );
    return infos;
}

void SourceCodeManager::loadFilesToCompile( vector<CodeInfo*>& filesToCompile, string configFilePath ) {
    filesToCompileManager->loadFilesToCompile( filesToCompile, allCodeInfosMap, configFilePath );
}

void SourceCodeManager::saveWritingTimeElapsedInFile( string configFilePath ) {
    filesToCompileManager->saveWritingTimesElapsedInFile( allCodeInfosMap, configFilePath );
}
