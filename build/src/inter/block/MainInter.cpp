
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

        if ( line.length() == 0 ) {
            lineNumber++;
            continue;
        }

        if ( line[ 0 ] == ' ' || line[ 0 ] == '\n' || line[ 0 ] == '\t' || line[ 0 ] == '\r' || line[ 0 ] == '#' ) {
            lineNumber++;
            continue;
        }

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
            cmds.push_back( cmd );
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

int MainInter::getCMDIntersLength() {
    return cmds.size();
}

CMDInter* MainInter::getCMDInterByIndex( int i ) {
    return cmds[ i ];
}

vector<CMDInter*> MainInter::getCMDInters() {
    return cmds;
}
