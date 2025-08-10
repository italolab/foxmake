
#include "Inter.h"

#include <sstream>

using std::stringstream;

inter_error::inter_error( string msg ) : runtime_error( msg ) {}

InterResult* Inter::replaceProps( string& line, int lineNumber, WithPropNo* no ) {
    size_t i = line.find( '$' );
    size_t j = line.find( '(' );

    if ( i != string::npos && j == i+1 ) {
        stringstream ss;

        int parentesisCount = 0;

        int len = line.length();
        for( int k = 0; k < len; k++ ) {
            if ( line[ k ] == '$' ) {
                if ( k+1 < len ) {
                    if ( line[ k+1 ] == '(' ) {
                        parentesisCount++;
                        int j = k+2;

                        while( parentesisCount > 0 && j < len ) {
                            if ( line[ j ] == '(' ) {
                                parentesisCount++;
                            } else if ( line[ j ] == ')' ) {
                                parentesisCount--;
                            }

                            if ( parentesisCount > 0 )
                                j++;
                        }
                        if ( parentesisCount == 0 ) {
                            string name = line.substr( k+2, j-(k+2) );
                            replaceProps( name, lineNumber, no );

                            if ( no->existsProperty( name ) ) {
                                string value = no->getPropertyValue( name );
                                ss << value;
                                k = j;
                            } else {
                                return new InterResult( 0, "Propriedade nao encontrada: $(" + name + ")" );
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
        line = ss.str();
    }

    return new InterResult( nullptr, 0 );
}
