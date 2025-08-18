
#include "Inter.h"
#include "../darv/MainScript.h"
#include "../msg/messagebuilder.h"
#include "../util/strutil.h"

#include "../error_messages.h"

#include <sstream>

using std::stringstream;

#include <iostream>
using namespace std;

inter_error::inter_error( string msg ) : runtime_error( msg ) {}

InterResult* Inter::replacePropsAndVarsAndDollarSigns( string& line, int lineNumber, Block* block ) {
    MainScript* script = (MainScript*)block->getRoot();

    size_t i = line.find( '$' );
    size_t j = line.find( '(' );
    if ( i != string::npos && j == i+1 ) {
        stringstream ss;

        int parentesisCount = 0;

        int len = line.length();
        for( int k = 0; k < len; k++ ) {
            bool isDollarSign = false;
            if ( k == 0 && line[ k ] == '$' )
                isDollarSign = true;

            if ( !isDollarSign && line[k] == '$') {
                if ( k > 0 )
                    isDollarSign = ( line[ k-1 ] != '\\' );
                else isDollarSign = true;
            }

            if ( isDollarSign ) {
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
                            replacePropsAndVarsAndDollarSigns( name, lineNumber, block );

                            if ( script->existsProperty( name ) ) {
                                string value = script->getPropertyValue( name );
                                ss << value;
                                k = j;
                            } else {
                                Var* var = block->getVar( name );
                                if ( var != nullptr ) {
                                    string value = var->getValue();
                                    ss << value;
                                    k = j;
                                } else {
                                    messagebuilder b( errors::PROP_OR_VAR_NOT_FOUND );
                                    b << name;
                                    return new InterResult( line, 0, 0, b.str() );
                                }
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
        line = strutil::replaceAll( line, "\\$", "$" );
    }
    return new InterResult( nullptr, 0, 0 );
}
