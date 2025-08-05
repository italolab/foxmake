
#include "Config.h"
#include "../util/interutil.h"

#include <fstream>
#include <sstream>

void Config::load( string file, vector<string> validStrCMDs ) {
    Property p;
    p.name = "config.file";
    p.value = file;
    properties.push_back( p );

    ifstream in( file );
    if ( !in.is_open() )
        throw inter_error( "Erro na abertura do arquivo de configuracao: " + file );

    string line;
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
            for( int k = 0; !isCmd && k < len; i++ ) {
                if ( cmd == validStrCMDs[ i ] ) {
                    line = interutil::replaceVars( line, cmd );
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

            value = interutil::replaceVars( value, name );

            Property p;
            p.name = name;
            p.value = value;
            properties.push_back( p );
        }
    }

    in.close();
}

int Config::getPropertiesLength() {
    return properties.size();
}

Property Config::getPropertyByIndex( int i ) {
    return properties[ i ];
}

string Config::getPropertyValue( string name ) {
    for( Property p : properties )
        if ( p.name == name )
            return p.value;
    return "";
}

vector<Property> Config::getProperties()  {
    return properties;
}

int Config::getCMDLength() {
    return cmds.size();
}

CMD* Config::getCMDByIndex( int i ) {
    return cmds[ i ];
}

vector<CMD*> Config::getCMDs() {
    return cmds;
}
