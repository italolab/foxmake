
#include "DependenciesSCLoader.h"
#include "../util/strutil.h"
#include "../io/io.h"

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

#include <iostream>
using std::cerr;
using std::endl;

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
        string filePath = info->filePath;
        vector<string>& includes = info->includes;
        vector<ClassInfo*>& classes = info->classes;
        for( ClassInfo* classInfo: classes ) {
            vector<string> extendedClasses = classInfo->extendedClasses;
            for( string exClass : extendedClasses ) {
                string classFilePath = this->findFilePathForClassName( allCodeInfosMap, includes, exClass, filePath );
                if ( classFilePath != "" )
                    info->dependencies.push_back( classFilePath );
            }
        }
    }

    return true;
}

/*
Para cada include, verifica as classes do arquivo correspondente ao include. Se alguma 
for igual a classe de que se está buscando o "filePath", então o filePath é retornado.

Exemplo:
    - O arquivo "a/AB.h" tem as classes A e B definidas.
    - A classe "c/C.h" inclue o arquivo "a/AB.h" e inclue também outros arquivos. Além disso, 
    - A classe "C" extende a classe "B";
    A busca vai testando include por include e, quando a busca chegar no include "a/AB.h", 
    então são recuperados os nomes das classes desse arquivo e, então, esses nomes de 
    classes ("A" e "B") são comparados com a classe extendida (que é a classe "B"). 
    Como a classe "B" é encontrada na lista de nomes de classes, o path do arquivo é 
    retornado: "a/AB.h"

Se o path não for encontrado, é retornada uma string vazia.
*/
string DependenciesSCLoader::findFilePathForClassName( 
            map<string, CodeInfo*>& allCodeInfosMap, 
            vector<string>& includePaths, 
            string className,
            string filePath ) {

    for( string includePath : includePaths ) {
        if ( allCodeInfosMap.find( includePath ) != allCodeInfosMap.end() ) {
            CodeInfo* info = allCodeInfosMap[ includePath ];
            for( ClassInfo* classInfo : info->classes ) {
                if ( classInfo->name == className )
                    return includePath;
            }
        }
    }
    return "";
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
        if ( !interpreted )
            classesSCInterpreter->interpretsClass( allCodeInfosMap, classToIncludeMap, in, line, filePath );        
    }

    in.close();
    return true;
}