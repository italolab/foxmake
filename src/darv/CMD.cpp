
#include "CMD.h"

CMD::CMD( Statement* parent, int numberOfLinesReaded, string line ) : GenericCMD( parent, numberOfLinesReaded, line ) {}

CMD::~CMD() {
    for( const auto& pair : propertiesMap )
        delete pair.second;
}

bool CMD::existsArg( string arg ) {
    for( string a : argsVect )
        if ( a == arg )
            return true;
    return false;
}

void CMD::addArg( string arg ) {
    argsVect.push_back( arg );
}

string CMD::getArgByIndex( int i ) {
    return argsVect[ i ];
}

int CMD::getArgsLength() {
    return argsVect.size();
}

vector<string>& CMD::getArgs() {
    return argsVect;
}

void CMD::addProperty( Prop* prop ) {
    propertiesMap[ prop->getName() ] = prop;
}

string CMD::getPropertyValue( string name ) {
    if ( propertiesMap.find( name ) != propertiesMap.end() )
        return propertiesMap[ name ]->getValue();
    return "";
}

vector<string> CMD::propertyNames() {
    vector<string> props;
    for( const auto& pair : propertiesMap )
        props.push_back( pair.first );
    return props;
}

int CMD::getPropertiesLength() {
    return propertiesMap.size();
}

map<string, Prop*>& CMD::getPropsMap() {
    return propertiesMap;
}

string CMD::getName() {
    return name;
}

string CMD::getCMDStr() {
    return cmdstr;
}

void CMD::setName( string name ) {
    this->name = name;
}

void CMD::setCMDStr( string cmdstr ) {
    this->cmdstr = cmdstr;
}

Statement* CMD::getTask() {
    return Statement::getTask();
}
