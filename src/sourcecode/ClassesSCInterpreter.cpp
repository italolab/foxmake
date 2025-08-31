
#include "ClassesSCInterpreter.h"
#include "../util/strutil.h"

#include <sstream>

using std::stringstream;

/*
Classe com método para interpretar as classes do arquivo de header ou código fonte 
e extrair e adicionar a estrutura o nome da classe e as classes que ela extende. 
Essa estrutura é adicionada a lista de classes do arquivo mapeada.
*/

void ClassesSCInterpreter::interpretsClass( 
            map<string, CodeInfo*>& allCodeInfosMap,
            ifstream& in, 
            string line, 

            string filePath ) {
                
    size_t i = 0;
    size_t j = 0;

    size_t k = line.find( "\"" );
    if ( k != string::npos )
        return;

    if ( strutil::startsWith( line, "class" ) ) {
        i = 0;
        j = 6;
    } else {
        i = line.find( " class " );
        if ( i == string::npos )
            return;

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

    vector<string> extendedClasses;

    ClassInfo* classInfo = new ClassInfo;
    classInfo->name = className;
    classInfo->extendedClasses = extendedClasses;

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
                    classInfo->extendedClasses.push_back( extendedClassName );                
            }

            if ( i == len && ch != '{' && !in.eof() ) {
                getline( in, line2 );
                i = 0;
            }
        }
    }

    if ( allCodeInfosMap.find( filePath ) != allCodeInfosMap.end() )
        allCodeInfosMap[ filePath ]->classes.push_back( classInfo );
}