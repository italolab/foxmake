
#include "IncludesSCInterpreter.h"
#include "../io/io.h"
#include "../util/strutil.h"

/*
Classe responsável por prover métodos para extrair os includes das classes 
e fazer o mapeamento entre cada classe e as que a incluem.

Isto é, é feito um mapeamento entre o path da classe e todos os paths de 
todas as classes que a incluem.

Logo, se uma classe A inclue as classes B, C e D, então o path da classe A é 
adicionado ao vetor de paths de classes das classes B, C e D.

São carregados também todos os includes do arquivo no vector de includes de CodeInfo.
*/

bool IncludesSCInterpreter::interpretsIncludes( 
            map<string, CodeInfo*>& allCodeInfosMap,
            string line, 
            string filePath ) {

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

            if ( allCodeInfosMap.find( filePath ) != allCodeInfosMap.end() )
                allCodeInfosMap[ filePath ]->includes.push_back( includePath );
                
            if ( allCodeInfosMap.find( includePath ) != allCodeInfosMap.end() )
                allCodeInfosMap[ includePath ]->dependencies.push_back( filePath );            
        }

        j = line.find( '\"', k+1 );
    }

    return true;
}