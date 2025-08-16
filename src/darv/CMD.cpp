
#include "CMD.h"

CMD::CMD( Statement* parent, int lineNumber, string line ) : Statement( parent, lineNumber, line ) {
    this->lineNumber = 0;
}

int CMD::countOpArgs() {
    int count = 0;
    for( string a : argsVect )
        if ( a.length() > 0 )
            if ( a[ 0 ] == '-' )
                count++;
    return count;
}

int CMD::countNoOpArgs() {
    int count = 0;
    for( string a : argsVect )
        if ( a.length() > 0 )
            if ( a[ 0 ] != '-' )
                count++;
    return count;
}

string CMD::getOpArg( int i ) {
    int k = 0;
    for( string a : argsVect ) {
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

string CMD::getNoOpArg( int i ) {
    int k = 0;
    for( string a : argsVect ) {
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
    for( string a : argsVect )
        if ( a == arg )
            return true;
    return false;
}

void CMD::addArg( string arg ) {
    argsVect.push_back( arg );
}

string CMD::getArg( int i ) {
    return argsVect[ i ];
}

int CMD::getArgsLength() {
    return argsVect.size();
}

vector<string>& CMD::args() {
    return argsVect;
}

void CMD::addProperty( Prop* prop ) {
    propertiesMap[ prop->getName() ] = prop;
}

string CMD::getPropertyValue( string name ) {
    Prop* prop = propertiesMap[ name ];
    if ( prop != nullptr )
        return prop->getValue();
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
