
#include "DependenciesSCLoader.h"
#include "../util/strutil.h"

/*
Classe responsável por prover métodos para carregamento das dependências entre 
as classes. Isto é, uma classe tem includes que são dependências e pode herdar de 
outras classes (também dependências).

Logo, se uma classe A inclue as classes B, C e D, então o path da classe A é 
adicionado ao vetor de paths de classes das classes B, C e D.

Os nomes dessas classes herdadas também são extraídos das classes, mapeados e 
adicionados como dependência. Ou seja, uma classe A que herda de B tem o path de B 
adicionado como mais uma de suas dependências.

Exemplo:

A classe "A" está definida no caminho: "a/A.h"
A classe "B" está definida no caminho: "b/B.h"
A classe "C" está definida no caminho: "c/C.h"
A classe "C" está definida no caminho: "d/D.h"

A classe "A" inclue "b/B.h" e herda de "D", então:
    - "a/A.h" é adicionado a lista de dependências de "b/B.h"
    - "a/A.h" é adicionado a lista de dependências de "c/C.h"
    - "d/D.h" é adicionado a lista de dependências de "a/A.h"
*/

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