
#include "CMD.h"

#include <sstream>
#include <cstring>

void CMD::interpreta( string command ) {
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

    interpreta( argc, argv );
}

void CMD::interpreta( int argc, char* argv[] ) {
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
                            throw runtime_error( "Valor com aspas duplas sem fechar." );
                        }
                    }
                }
            }

            CMDProperty prop;
            prop.name = name;
            prop.value = value;
            properties.push_back( prop );
        } else {
            string paramStr( param );
            args.push_back( paramStr );
        }
    }
}

string CMD::getOpArg( int i ) {
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

string CMD::getNotOpArg( int i ) {
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

bool CMD::existsArg( string arg ) {
    for( string a : args )
        if ( a == arg )
            return true;
    return false;
}

void CMD::addArg( string arg ) {
    args.push_back( arg );
}

string CMD::getArg( int i ) {
    return args[ i ];
}

string CMD::getPropertyValue( string name ) {
    for( CMDProperty p : properties )
        if ( p.name == name )
            return p.value;
    return "";
}

CMDProperty CMD::getPropertyByIndex( int i ) {
    return properties[ i ];
}

vector<string> CMD::getArgs() {
    return args;
}

vector<CMDProperty> CMD::getProperties() {
    return properties;
}

int CMD::getArgsLength() {
    return args.size();
}

int CMD::getPropertiesLength() {
    return properties.size();
}

string CMD::getName() {
    return name;
}

string CMD::getCMDStr() {
    return cmdstr;
}
