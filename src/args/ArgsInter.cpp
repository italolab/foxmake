
#include "ArgsInter.h"

Args* ArgsInter::exec( int argc, char* argv[] ) {
    Args* args = new Args();

    bool errorFound = false;

    for( int i = 1; !errorFound && i < argc; i++ ) {
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
                            args->setError( "Valor com aspas duplas sem fechar." );
                            errorFound = true;
                        }
                    }
                }
            }
            if ( !errorFound )
                args->addArg( name, value );
        } else {
            string paramStr( param );
            args->addCommand( paramStr );
        }
    }

    return args;
}
