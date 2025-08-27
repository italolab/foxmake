
#include "OutputThread.h"

OutputThread::OutputThread( string name ) {
    this->name = name;
    this->finishFlag = false;
}

void OutputThread::run( FILE* pipe ) {
    char buffer[ 128 ];
    while( fgets( buffer, sizeof( buffer ), pipe ) != nullptr )
        this->addOutput( buffer );

    this->finish();
}

void OutputThread::finish() {
    std::lock_guard<std::mutex> lock( mtx );

    finishFlag = true;    
}

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

string OutputThread::getName() {
    return name;
}

bool OutputThread::isFinished() {
    return finishFlag;
}