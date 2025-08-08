
#include "inter.h"
#include "interexcept.h"

#include <sstream>

namespace inter {

    string replaceVars( string line, int lineNumber, WithPropInter* inter ) {
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
                                name = replaceVars( name, lineNumber, inter );

                                if ( inter->existsProperty( name ) ) {
                                    string value = inter->getPropertyValue( name );
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

}
