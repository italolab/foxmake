
#include "CMDInter.h"
#include "InterManager.h"
#include "../darv/CMD.h"
#include "../darv/Prop.h"
#include "../util/strutil.h"

#include "../error_messages.h"

#include <sstream>
#include <cstring>

using std::istringstream;
using std::stringstream;

InterResult* CMDInter::interpretsMainCMD( int argc, char* argv[], void* mgr ) {
    int numberOfLinesReaded = 0;
    return interprets( nullptr, argc, argv, numberOfLinesReaded, mgr );
}

InterResult* CMDInter::interprets( Block* parent, string line, int& numberOfLinesReaded, void* mgr ) {
    string cmdstr = line;

    InterResult* replaceResult = Inter::replacePropsAndVarsAndDollarSigns( line, cmdstr, numberOfLinesReaded, parent );
    if ( !replaceResult->isInterpreted() )
        return replaceResult;

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

    return interprets( parent, argc, argv, numberOfLinesReaded, mgr );
}

InterResult* CMDInter::interprets( Block* parent, int argc, char* argv[], int& numberOfLinesReaded, void* mgr ) {
    string line = "";
    string cmdName = "";
    if ( argc > 0 ) {
        cmdName = argv[ 0 ];

        stringstream ss;
        for( int i = 0; i < argc; i++ ) {
            ss << argv[ i ];
            if ( i < argc-1 )
                ss << " ";
        }
        line = ss.str();
    }

    CMD* cmd = new CMD( parent, numberOfLinesReaded, line );
    cmd->setName( cmdName );
    cmd->setCMDStr( line );
    
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
                            return new InterResult( line, numberOfLinesReaded, 0, errors::VALUE_IN_QUOTES_NOT_CLOSED );
                        }
                    }
                }
            }

            cmd->addProperty( new Prop( cmd, name, value, numberOfLinesReaded, line ) );
        }
        
        cmd->addArg( param );
    }

    if ( parent != nullptr )
        parent->addStatement( cmd );

    numberOfLinesReaded++;

    return new InterResult( cmd, numberOfLinesReaded, 0 );
}
