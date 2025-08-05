
#include "Properties.h"
#include "utilexcept.h"

#include <fstream>
#include <sstream>

void Properties::load( string file ) {
    add( "config.file", file );

    ifstream in( file );
    if ( !in.is_open() )
        throw prop_error( "Erro na abertura do arquivo de configuracao: " + file );

    string line;
    while( getline( in, line ) ) {
        if ( line.length() == 0 )
            continue;
        if ( line[ 0 ] == ' ' || line[ 0 ] == '\n' || line[ 0 ] == '\t' || line[ 0 ] == '\r' || line[ 0 ] == '#' )
            continue;

        size_t i = line.find( '=' );
        if ( i == string::npos ) {
            in.close();
            throw prop_error( "Propriedade em formato inválido: " + line );
        }

        string name = line.substr( 0, i );
        string value = line.substr( i+1, line.length()-i );

        i = value.find( '$' );
        size_t j = value.find( '(' );

        if ( i != string::npos && j == i+1 ) {
            stringstream ss;

            int len = value.length();
            for( int k = 0; k < len; k++ ) {
                if ( value[ k ] == '$' ) {
                    if ( k+1 < len ) {
                        if ( value[ k+1 ] == '(' ) {
                            j = value.find( ')', k+2 );
                            if ( j != string::npos ) {
                                string name2 = value.substr( k+2, j-(k+2) );
                                string value2 = getProperty( name2 );
                                if ( value2 != "" ) {
                                    ss << value2;
                                    k = j;
                                } else {
                                    throw prop_error( "Lendo propriedade: " + name + ";\nPropriedade nao encontrada: $(" + name2 + ")" );
                                }
                            } else {
                                ss << value[ k ];
                            }
                        } else {
                            ss << value[ k ];
                        }
                    } else {
                        ss << value[ k ];
                    }
                } else {
                    ss << value[ k ];
                }

            }
            value = ss.str();
        }

        add( name, value );
    }

    in.close();
}

void Properties::add( string name, string value ) {
    Property p;
    p.name = name;
    p.value = value;
    properties.push_back( p );
}

int Properties::length() {
    return properties.size();
}

Property Properties::get( int i ) {
    return properties[ i ];
}

string Properties::getProperty( string name ) {
    for( Property p : properties )
        if ( p.name == name )
            return p.value;
    return "";
}

vector<Property> Properties::getAll()  {
    return properties;
}
