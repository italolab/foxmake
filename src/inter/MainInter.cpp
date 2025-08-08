
#include "MainInter.h"

#include <fstream>
#include <sstream>
#include <iostream>

void MainInter::interpreta( string file, vector<string> validStrCMDs ) {
    Property p;
    p.name = "config.file";
    p.value = file;
    properties.push_back( p );

    ifstream in( file );
    if ( !in.is_open() )
        throw inter_error( "Erro na abertura do arquivo de configuracao: " + file );

    string line;
    int lineNumber = 1;
    while( getline( in, line ) ) {
        if ( line.length() == 0 )
            continue;
        if ( line[ 0 ] == ' ' || line[ 0 ] == '\n' || line[ 0 ] == '\t' || line[ 0 ] == '\r' || line[ 0 ] == '#' )
            continue;

        bool isCmd = false;

        size_t i = line.find( ' ' );
        if ( i != string::npos ) {
            string cmd = line.substr( 0, i );
            int len = validStrCMDs.size();
            for( int k = 0; !isCmd && k < len; k++ ) {
                if ( cmd == validStrCMDs[ k ] ) {
                    line = replaceVars( line, lineNumber );
                    isCmd = true;
                }
            }
        }

        if ( isCmd ) {
            CMD* cmd = new CMD();
            cmd->interpreta( line );
            cmds.push_back( cmd );
        } else {
            i = line.find( '=' );
            if ( i == string::npos ) {
                in.close();
                throw inter_error( "Propriedade em formato inválido: " + line );
            }

            string name = line.substr( 0, i );
            string value = line.substr( i+1, line.length()-i );

            value = replaceVars( value, lineNumber );

            Property p;
            p.name = name;
            p.value = value;
            properties.push_back( p );
        }
        lineNumber++;
    }

    in.close();
}

int MainInter::getPropertiesLength() {
    return properties.size();
}

Property MainInter::getPropertyByIndex( int i ) {
    return properties[ i ];
}

string MainInter::getPropertyValue( string name ) {
    for( Property p : properties )
        if ( p.name == name )
            return p.value;
    return "";
}

bool MainInter::existsProperty( string name ) {
    for( Property p : properties )
        if ( p.name == name )
            return true;
    return false;
}

vector<Property> MainInter::getProperties()  {
    return properties;
}

int MainInter::getCMDLength() {
    return cmds.size();
}

CMD* MainInter::getCMDByIndex( int i ) {
    return cmds[ i ];
}

vector<CMD*> MainInter::getCMDs() {
    return cmds;
}
