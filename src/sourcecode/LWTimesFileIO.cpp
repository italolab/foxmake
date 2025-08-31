
#include "LWTimesFileIO.h"
#include "../io/io.h"

#include <fstream>

using std::ifstream;
using std::ofstream;

/*
Classe responsável por prover métodos para carregar e salvar o arquivo de 
tempo de última escrita de cada arquivo de código fonte.
*/

bool LWTimesFileIO::loadLastWriteTimesFromFile( map<string, long>& writingTimesElapsedMap, string configFilePath ) {
    ifstream in( configFilePath );
    if ( !in.is_open() )
        return false;

    while( !in.eof() ) {
        string line;
        getline( in, line );

        size_t i = line.find( '=' );
        if ( i != string::npos ) {
            string filePath = line.substr( 0, i );
            string lastWriteTime = line.substr( i+1, line.length()-i+2 );

            writingTimesElapsedMap[ filePath ] = std::stol( lastWriteTime );
        }
    }

    in.close();
    return true;
}

bool LWTimesFileIO::saveLastWriteTimesInFile( map<string, CodeInfo*>& allSourceInfosMap, string configFileName, bool isAppend ) {
    ofstream out( configFileName, isAppend ? std::ios::app : std::ios::out );
    if ( !out.is_open() )
        return false;

    for( const auto& pair : allSourceInfosMap ) {
        string filePath = pair.second->filePath;

        long lastWriteTime = io::lastWriteTime( filePath );
        out << filePath << "=" << lastWriteTime << "\n";
    }

    out.close();
    return true;
}
