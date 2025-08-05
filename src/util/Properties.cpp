
#include "Properties.h"
#include "utilexcept.h"

#include <fstream>

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
