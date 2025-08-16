
#include "FileIterator.h"

using std::ifstream;

namespace fileit {

    file_not_open_error::file_not_open_error( string msg ) : runtime_error( msg ) {}

}

FileIterator::FileIterator( string file ) {
    ifstream* in = new ifstream( file );
    if ( !in->is_open() )
        throw fileit::file_not_open_error( "Nao foi possivel abrir o arquivo: \"" + file + "\"" );
    this->stream = in;
}

FileIterator::~FileIterator() {
    delete stream;
}

bool FileIterator::hasNextLine() {
    if ( stream->eof() ) {
        if ( stream->is_open() )
            stream->close();
        return false;
    }
    return true;
}

string FileIterator::nextLine() {
    string line;
    getline( *stream, line );
    return line;
}


