
#include "Args.h"

Args::Args() {
    this->errorFound = false;
}

void Args::setError( string err ) {
    this->error = err;
    this->errorFound = true;
}

bool Args::existsCommand( string command ) {
    for( string cmd : commands )
        if ( cmd == command )
            return true;
    return false;
}

void Args::addCommand( string command ) {
    commands.push_back( command );
}

void Args::addArg( string name, string value ) {
    Arg arg;
    arg.name = name;
    arg.value = value;
    args.push_back( arg );
}

string Args::getCommand( int i ) {
    return commands[ i ];
}

Arg Args::getArg( int i ) {
    return args[ i ];
}

vector<string> Args::getCommands() {
    return commands;
}

vector<Arg> Args::getArgs() {
    return args;
}

int Args::getCommandsLength() {
    return commands.size();
}

int Args::getArgsLength() {
    return args.size();
}

string Args::getError() {
    return error;
}

bool Args::isErrorFound() {
    return errorFound;
}
