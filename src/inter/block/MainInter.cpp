
#include "MainInter.h"
#include "it/StringIterator.h"
#include "../inter.h"
#include "../interexcept.h"

#include <fstream>
#include <sstream>
#include <iostream>

MainInter::MainInter( MainInterDriver* drv ) {
    this->drv = drv;
}

void MainInter::interpreta( BlockIterator* blockIt ) {
    vector<string> validCMDs = drv->validMainCMDNames();

    string line;
    int lineNumber = 1;
    while( blockIt->hasNextLine() ) {
        string line = blockIt->nextLine();

        if ( line.length() == 0 )
            continue;
        if ( line[ 0 ] == ' ' || line[ 0 ] == '\n' || line[ 0 ] == '\t' || line[ 0 ] == '\r' || line[ 0 ] == '#' )
            continue;

        bool isCmd = false;

        size_t i = line.find( ' ' );
        if ( i != string::npos ) {
            string cmd = line.substr( 0, i );
            int len = validCMDs.size();
            for( int k = 0; !isCmd && k < len; k++ ) {
                if ( cmd == validCMDs[ k ] ) {
                    line = inter::replaceVars( line, lineNumber, this );
                    isCmd = true;
                }
            }
        }

        if ( isCmd ) {
            CMDInter* cmd = new CMDInter();
            cmd->interpreta( line, lineNumber );
            cmdsMap[ cmd->getName() ] = cmd;
        } else {
            i = line.find( '=' );
            if ( i == string::npos ) {
                stringstream ss;
                ss << "Erro na linha: " << lineNumber << ";\nPropriedade em formato inválido: \"" << line << "\"";
                throw inter_error( ss.str() );
            }

            string name = line.substr( 0, i );
            string value = line.substr( i+1, line.length()-i );

            value = inter::replaceVars( value, lineNumber, this );

            propertiesMap[ name ] = value;
        }
        lineNumber++;
    }
}

int MainInter::getPropertiesLength() {
    return propertiesMap.size();
}

string MainInter::getPropertyValue( string name ) {
    return propertiesMap[ name ];
}

bool MainInter::existsProperty( string name ) {
    return propertiesMap.find( name ) != propertiesMap.end();
}

vector<string> MainInter::propertyNames()  {
    vector<string> props;
    for( const auto& pair : propertiesMap )
        props.push_back( pair.first );
    return props;
}

int MainInter::getCMDsLength() {
    return cmdsMap.size();
}

CMDInter* MainInter::getCMDByIndex( int i ) {
    int k = 0;
    for( const auto& pair : cmdsMap ) {
        if ( k == i )
           return pair.second;
        k++;
    }
    return nullptr;
}

vector<string> MainInter::cmdNames() {
    vector<string> cmds;
    for( const auto& pair : propertiesMap )
        cmds.push_back( pair.first );
    return cmds;
}
