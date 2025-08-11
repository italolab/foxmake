
#include "CMDInter.h"
#include "InterManager.h"
#include "../darv/CMD.h"
#include "../darv/Prop.h"

#include <sstream>
#include <cstring>

using std::istringstream;
using std::stringstream;

#include <iostream>
using namespace std;

InterResult* CMDInter::interpretaMainCMD( int argc, char* argv[], InterManager* manager ) {
    return interpreta( nullptr, argc, argv, 0, manager );
}

InterResult* CMDInter::interpreta( Block* block, string cmdstr, int lineNumber, InterManager* manager ) {
    string token;
    istringstream iss( cmdstr );

    int argc = 0;
    while( getline( iss, token, ' ' ) )
        argc++;

    char* argv[ argc ];

    istringstream iss2( cmdstr );
    int i = 0;
    while( getline( iss2, token, ' ' ) )
        argv[ i++ ] = strdup( token.c_str() );

    return interpreta( block, argc, argv, lineNumber, manager );
}

InterResult* CMDInter::interpreta( Block* block, int argc, char* argv[], int lineNumber, InterManager* manager ) {
    CMD* cmd = new CMD( block );
    cmd->setLineNumber( lineNumber );

    if ( argc > 0 ) {
        cmd->setName( argv[ 0 ] );

        stringstream ss;
        for( int i = 0; i < argc; i++ ) {
            ss << argv[ i ];
            if ( i < argc-1 )
                ss << " ";
        }
        cmd->setCMDStr( ss.str() );
    }

    for( int i = 1; i < argc; i++ ) {
        string param( argv[ i ] );

        size_t j = param.find( '=' );

        if ( j != string::npos ) {
            string name = param.substr( 0, j );
            string value = param.substr( j+1, param.length()-j );

            int len = value.length();
            if ( len > 0 ) {
                if ( value[ 0 ] == '\"' ) {
                    if ( value[ len-1 ] == '\"' ) {
                        value = value.substr( 1, len-2 );
                    } else {
                        i++;
                        bool stop = false;
                        while( !stop && i < argc ) {
                            string param2( argv[ i ] );
                            if ( param2[ len-1 ] == '\"' ) {
                                stop = true;
                            } else {
                                i++;
                            }
                            value += param2;
                        }

                        if ( stop ) {
                            value = value.substr( 1, len-2 );
                        } else {
                            return new InterResult( 0, 0, "Valor com aspas duplas sem fechar." );
                        }
                    }
                }
            }

            cmd->addProperty( new Prop( name, value ) );
        } else {
            cmd->addArg( param );
        }
    }

    if ( block != nullptr )
        block->addCMD( cmd );
    return new InterResult( cmd, 0, 0 );
}
