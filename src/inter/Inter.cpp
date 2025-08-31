
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

InterResult* Inter::replacePropsAndVarsAndDollarSigns( 
        string line, string& text, int& numberOfLinesReaded, Block* block ) {

    MainScript* script = (MainScript*)block->getRoot();

    size_t i = text.find( '$' );
    size_t j = text.find( '(' );
    if ( i != string::npos && j == i+1 ) {
        stringstream ss;

        int parentesisCount = 0;

        int len = text.length();
        for( int k = 0; k < len; k++ ) {
            bool isDollarSign = false;
            if ( k == 0 && text[ k ] == '$' )
                isDollarSign = true;

            if ( !isDollarSign && text[k] == '$') {
                if ( k > 0 )
                    isDollarSign = ( text[ k-1 ] != '\\' );
                else isDollarSign = true;
            }

            if ( isDollarSign ) {
                if ( k+1 < len ) {
                    if ( text[ k+1 ] == '(' ) {
                        parentesisCount++;
                        int j = k+2;

                        while( parentesisCount > 0 && j < len ) {
                            if ( text[ j ] == '(' ) {
                                parentesisCount++;
                            } else if ( text[ j ] == ')' ) {
                                parentesisCount--;
                            }

                            if ( parentesisCount > 0 )
                                j++;
                        }
                        if ( parentesisCount == 0 ) {
                            string name = text.substr( k+2, j-(k+2) );
                            replacePropsAndVarsAndDollarSigns( line, name, numberOfLinesReaded, block );

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
                                    return new InterResult( line, numberOfLinesReaded, 0, b.str() );
                                }
                            }
                        } else {
                            ss << text[ k ];
                        }
                    } else {
                        ss << text[ k ];
                    }
                } else {
                    ss << text[ k ];
                }
            } else {
                ss << text[ k ];
            }
        }
        text = ss.str();
        text = strutil::replaceAll( text, "\\$", "$" );
    }
    return new InterResult( nullptr, 0, 0 );
}
