
#include "ExecCMD.h"

ExecCMD::ExecCMD( CMD* cmd ) {
    vector<string>& args = cmd->getArgs();
    map<string, Prop*> props = cmd->getPropsMap();

    this->name = cmd->getName();
    this->cmdstr = cmd->getCMDStr();
    this->argsVect.insert( argsVect.end(), args.begin(), args.end() );
    
    for( const auto& pair : props )
        this->propsMap[ pair.first ] = pair.second;

    this->cmd = cmd;
}

vector<string> ExecCMD::getOpArgValues( string op ) {
    vector<string> values;
    int len = argsVect.size();
    for( int i = 0; i < len; i++ ) {
        if ( argsVect[ i ] == op && i+1 < len )
            if ( argsVect[ i+1 ] != op )
                values.push_back( argsVect[ i+1 ] );    
    }
    return values;
}

int ExecCMD::countOpArgs() {
    int count = 0;
    for( string a : argsVect )
        if ( a.length() > 0 )
            if ( a[ 0 ] == '-' )
                count++;
    return count;
}

int ExecCMD::countNoOpArgs() {
    int count = 0;
    for( string a : argsVect )
        if ( a.length() > 0 )
            if ( a[ 0 ] != '-' )
                count++;
    return count;
}

string ExecCMD::getOpArgByIndex( int i ) {
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

string ExecCMD::getNoOpArgByIndex( int i ) {
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

bool ExecCMD::existsArg( string arg ) {
    for( string a : argsVect )
        if ( a == arg )
            return true;
    return false;
}

string ExecCMD::getArgByIndex( int i ) {
    return argsVect[ i ];
}

int ExecCMD::getArgsLength() {
    return argsVect.size();
}

vector<string>& ExecCMD::getArgs() {
    return argsVect;
}

string ExecCMD::getPropertyValue( string name ) {
    Prop* prop = this->getProperty( name );
    if ( prop != nullptr )
        return prop->getValue();
    return "";
}

Prop* ExecCMD::getProperty( string name ) {
    if ( propsMap.find( name ) != propsMap.end() )
        return propsMap[ name ];
    return nullptr;
}

string ExecCMD::getName() {
    return name;
}

string ExecCMD::getCMDStr() {
    return cmdstr;
}

CMD* ExecCMD::getCMD() {
    return cmd;
}

void ExecCMD::setCMDStr( string cmdstr ) {
    this->cmdstr = cmdstr;
}