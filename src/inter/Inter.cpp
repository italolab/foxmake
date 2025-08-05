
#include "Inter.h"

#include <sstream>

inter_error::inter_error( string msg ) : runtime_error( msg ) {}

string Inter::replaceVars( string line, int lineNumber ) {
    size_t i = line.find( '$' );
    size_t j = line.find( '(' );

    if ( i != string::npos && j == i+1 ) {
        stringstream ss;

        int len = line.length();
        for( int k = 0; k < len; k++ ) {
            if ( line[ k ] == '$' ) {
                if ( k+1 < len ) {
                    if ( line[ k+1 ] == '(' ) {
                        j = line.find( ')', k+2 );
                        if ( j != string::npos ) {
                            string name = line.substr( k+2, j-(k+2) );
                            string value = getPropertyValue( name );
                            if ( value != "" ) {
                                ss << value;
                                k = j;
                            } else {
                                stringstream ss2;
                                ss2 << "Linha(" << lineNumber << ") --> Propriedade nao encontrada: $(" << name << ")";
                                throw inter_error( ss2.str() );
                            }
                        } else {
                            ss << line[ k ];
                        }
                    } else {
                        ss << line[ k ];
                    }
                } else {
                    ss << line[ k ];
                }
            } else {
                ss << line[ k ];
            }
        }
        return ss.str();
    }
    return line;
}
