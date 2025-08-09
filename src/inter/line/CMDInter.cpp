
#include "CMDInter.h"
#include "../interexcept.h"

#include <sstream>
#include <cstring>

CMDInter::CMDInter() {
    this->lineNumber = 0;
}

void CMDInter::interpreta( string command, int lineNumber ) {
    this->lineNumber = lineNumber;

    string token;
    istringstream iss( command );

    int argc = 0;
    while( getline( iss, token, ' ' ) )
        argc++;

    char* argv[ argc ];

    istringstream iss2( command );
    int i = 0;
    while( getline( iss2, token, ' ' ) )
        argv[ i++ ] = strdup( token.c_str() );

    interpreta( argc, argv, lineNumber );
}

void CMDInter::interpreta( int argc, char* argv[], int lineNumber ) {
    if ( argc > 0 ) {
        this->name = argv[ 0 ];

        stringstream ss;
        for( int i = 0; i < argc; i++ ) {
            ss << argv[ i ];
            if ( i < argc-1 )
                ss << " ";
        }
        this->cmdstr = ss.str();
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
                            throw inter_error( "Valor com aspas duplas sem fechar." );
                        }
                    }
                }
            }

            propertiesMap[ name ] = value;
        } else {
            string paramStr( param );
            args.push_back( paramStr );
        }
    }
}

string CMDInter::getOpArg( int i ) {
    int k = 0;
    for( string a : args ) {
        if ( a.length() > 0 ) {
            if ( a[ 0 ] == '-' ) {
                if ( i == k )
                    return a;
                k++;
            }
        }
    }
    return "";
}

string CMDInter::getNotOpArg( int i ) {
    int k = 0;
    for( string a : args ) {
        if ( a.length() > 0 ) {
            if ( a[ 0 ] != '-' ) {
                if ( i == k )
                    return a;
                k++;
            }
        }
    }
    return "";
}

bool CMDInter::existsArg( string arg ) {
    for( string a : args )
        if ( a == arg )
            return true;
    return false;
}

void CMDInter::addArg( string arg ) {
    args.push_back( arg );
}

string CMDInter::getArg( int i ) {
    return args[ i ];
}

string CMDInter::getPropertyValue( string name ) {
    return propertiesMap[ name ];
}

vector<string> CMDInter::getArgs() {
    return args;
}

vector<string> CMDInter::propertyNames() {
    vector<string> props;
    for( const auto& pair : propertiesMap )
        props.push_back( pair.first );
    return props;
}

int CMDInter::getArgsLength() {
    return args.size();
}

int CMDInter::getPropertiesLength() {
    return propertiesMap.size();
}

string CMDInter::getName() {
    return name;
}

string CMDInter::getCMDStr() {
    return cmdstr;
}

int CMDInter::getLineNumber() {
    return lineNumber;
}
