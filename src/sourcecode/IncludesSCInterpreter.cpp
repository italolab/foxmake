
#include "IncludesSCInterpreter.h"
#include "../io/io.h"
#include "../util/strutil.h"

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

            if ( allCodeInfosMap.find( includePath ) != allCodeInfosMap.end() )
                allCodeInfosMap[ includePath ]->dependencies.push_back( filePath );
        }

        j = line.find( '\"', k+1 );
    }

    return true;
}