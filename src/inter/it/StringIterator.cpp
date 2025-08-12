
#include "StringIterator.h"

using std::getline;

StringIterator::StringIterator( string str ) {
    this->stream = new istringstream( str );
}

bool StringIterator::hasNextLine() {
    return stream->peek() != EOF;
}

string StringIterator::nextLine() {
    string line;
    getline( *stream, line, '\n' );
    return line;
}
