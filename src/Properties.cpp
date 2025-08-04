
#include "Properties.h"

void Properties::load( string file ) {
    add( "includeDirs", "-Iinclude" );
    add( "defines", "-DBUILDING_DLL" );
    add( "compiler", "g++" );
    add( "compilerParams", "-Wall -g" );
    add( "otherCompileParams", "" );
    add( "srcDir", "src/" );
    add( "debugDir", "bin/Debug/" );
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
