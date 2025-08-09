
#include "MainScript.h"

MainScript::MainScript() : Block( nullptr ) {}

void MainScript::addProperty( string name, string value ) {
    propertiesMap[ name ] = new Property( this, name, value );
}

int MainScript::getPropertiesLength() {
    return propertiesMap.size();
}

string MainScript::getPropertyValue( string name ) {
    return propertiesMap[ name ]->getValue();
}

bool MainScript::existsProperty( string name ) {
    return propertiesMap.find( name ) != propertiesMap.end();
}

vector<string> MainScript::propertyNames() {
    vector<string> names;
    for( const auto& pair : propertiesMap )
        names.push_back( pair.first );
    return names;
}

void MainScript::addCMD( CMD* cmd ) {
    cmdsVect.push_back( cmd );
}

int MainScript::getCMDsLength() {
    return cmdsVect.size();
}

CMD* MainScript::getCMD( string name ) {
    for( CMD* cmd : cmdsVect )
        if ( cmd->getName() == name )
            return cmd;
    return nullptr;
}

CMD* MainScript::getCMDByIndex( int i ) {
    int k = 0;
    for( CMD* cmd : cmdsVect ) {
        if ( k == i )
            return cmd;
        k++;
    }
    return nullptr;
}

vector<CMD*> MainScript::cmds() {
    return cmdsVect;
}
