
#include "OutputThread.h"

OutputThread::OutputThread( string name ) {
    this->name = name;
}

#ifdef _WIN32

void OutputThread::run( HANDLE hStdOutRead ) {
    const DWORD BUFFER_SIZE = 4096;
    char buffer[ BUFFER_SIZE ];
    DWORD bytesRead;

    bool isEnd = false;
    while( !isEnd ) {
        WINBOOL res = ReadFile( hStdOutRead, buffer, BUFFER_SIZE-1, &bytesRead, NULL );
        if ( !res || bytesRead == 0 ) {
            isEnd = true;
        } else {
            buffer[ bytesRead ] = '\0';
            this->addOutput( buffer );
        }
    }

    {
        std::lock_guard<std::mutex> lock( mtx );
        finishFlag = true;
    }
}

#else

void OutputThread::run( FILE* pipe ) {
    char buffer[ 128 ];
    while( fgets( buffer, sizeof( buffer ), pipe ) != nullptr )
        this->addOutput( buffer );

    {
        std::lock_guard<std::mutex> lock( mtx );
        finishFlag = true;
    }
}

#endif

void OutputThread::addOutput( string output ) {
    std::lock_guard<std::mutex> lock( mtx );

    outputQueue.push( output );
}

bool OutputThread::hasNextOutput() {
    std::lock_guard<std::mutex> lock( mtx );

    return !outputQueue.empty();
}

string OutputThread::nextOutput(){
    std::lock_guard<std::mutex> lock( mtx );

    string output = outputQueue.front();
    outputQueue.pop();
    return output;
}

bool OutputThread::isFinished() {
    return finishFlag;
}