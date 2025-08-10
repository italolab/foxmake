
#include "CMD.h"
#include "Property.h"

CMD::CMD( Block* parent ) : No( parent ) {
    this->lineNumber = 0;
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

void CMD::addProperty( string name, string value ) {
    propertiesMap[ name ] = new Property( name, value );
}

string CMD::getPropertyValue( string name ) {
    return propertiesMap[ name ]->getValue();
}

vector<string> CMD::getArgs() {
    return args;
}

vector<string> CMD::propertyNames() {
    vector<string> props;
    for( const auto& pair : propertiesMap )
        props.push_back( pair.first );
    return props;
}

int CMD::getArgsLength() {
    return args.size();
}

int CMD::getPropertiesLength() {
    return propertiesMap.size();
}

string CMD::getName() {
    return name;
}

string CMD::getCMDStr() {
    return cmdstr;
}

int CMD::getLineNumber() {
    return lineNumber;
}

void CMD::setName( string name ) {
    this->name = name;
}

void CMD::setCMDStr( string cmdstr ) {
    this->cmdstr = cmdstr;
}

void CMD::setLineNumber( int lineNumber ) {
    this->lineNumber = lineNumber;
}
