
#include "StringIterator.h"

using std::getline;

StringIterator::StringIterator( string str ) {
    this->stream = new istringstream( str );
}

bool StringIterator::hasNextLine() {
    char ch = stream->peek();
    if ( ch == '\n' )
        stream->get();
    return ch != EOF;
}

string StringIterator::nextLine() {
    string line;
    getline( *stream, line, '\n' );
    return line;
}
