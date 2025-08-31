
#include "DependenciesSCLoader.h"
#include "../util/strutil.h"

DependenciesSCLoader::DependenciesSCLoader() {
    includesSCInterpreter = new IncludesSCInterpreter();
    classesSCInterpreter = new ClassesSCInterpreter();
}

DependenciesSCLoader::~DependenciesSCLoader() {
    delete includesSCInterpreter;
    delete classesSCInterpreter;
}

bool DependenciesSCLoader::loadDependencies( 
            map<string, CodeInfo*>& allCodeInfosMap,
            map<string, string>& classToIncludeMap ) {

    for( const auto& pair : allCodeInfosMap )
        ((CodeInfo*)pair.second)->dependencies.clear();

    for( const auto& pair : allCodeInfosMap ) {
        CodeInfo* info = pair.second;
        
        bool ok = this->loadDepencenciesForFile( 
                allCodeInfosMap, classToIncludeMap, info->filePath );

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

bool DependenciesSCLoader::loadDepencenciesForFile( 
            map<string, CodeInfo*>& allCodeInfosMap, 
            map<string, string>& classToIncludeMap,
            string filePath ) {

    ifstream in( filePath );
    if ( !in.is_open() )
        return false;

    string line;
    while( !in.eof() ) {
        getline( in, line );
        line = strutil::removeStartWhiteSpaces( line );

        bool interpreted = includesSCInterpreter->interpretsIncludes( allCodeInfosMap, line, filePath );
        if ( !interpreted ) {
            interpreted = classesSCInterpreter->interpretsClass(
                    allCodeInfosMap, classToIncludeMap, in, line, filePath );
        }
    }

    in.close();
    return true;
}