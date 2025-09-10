
#include "CMD.h"

CMD::CMD( Statement* parent, int numberOfLinesReaded, string line ) : GenericCMD( parent, numberOfLinesReaded, line ) {}

CMD::~CMD() {
    for( const auto& pair : propertiesMap )
        delete pair.second;
}

CMD* CMD::newCopy() {
    Statement* parent = Statement::getParent();
    int numberOfLinesReaded = Statement::getNumberOfLinesReaded();
    string line = Statement::getLine();
    
    CMD* cmd = new CMD( parent, numberOfLinesReaded, line );
    cmd->load( name, cmdstr, argsVect, propertiesMap );
    
    return cmd;
}

void CMD::load( string name, string cmdstr, vector<string>& argsVect2, map<string, Prop*>& propsMap2 ) {
    this->name = name;
    this->cmdstr = cmdstr;
    this->argsVect.insert( argsVect.end(), argsVect2.begin(), argsVect2.end() );
    
    for( const auto& pair : propsMap2 )
        this->propertiesMap[ pair.first ] = pair.second;    
}


vector<string> CMD::getOpArgValues( string op ) {
    vector<string> values;
    int len = argsVect.size();
    for( int i = 0; i < len; i++ ) {
        if ( argsVect[ i ] == op && i+1 < len )
            if ( argsVect[ i+1 ] != op )
                values.push_back( argsVect[ i+1 ] );    
    }
    return values;
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

string CMD::getOpArgByIndex( int i ) {
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

string CMD::getNoOpArgByIndex( int i ) {
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
