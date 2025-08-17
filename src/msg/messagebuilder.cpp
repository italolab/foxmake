
#include "messagebuilder.h"

#include "../util/strutil.h"

messagebuilder::messagebuilder() {}

messagebuilder::messagebuilder( string msg ) {
    this->message = msg;
}

messagebuilder::~messagebuilder() {}

messagebuilder& messagebuilder::operator<<( string param ) {
    params.push_back( param );
    return *this;
}

string messagebuilder::str() {
    string msg = message;
    int paramsLen = params.size();
    for( int i = 0; i < paramsLen; i++ )
        msg = strutil::replace( msg, "$" + std::to_string(i+1), params[ i ] );
    return msg;
}
