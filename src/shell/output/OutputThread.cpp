
#include "OutputThread.h"

#include <cstring>
#include <iostream>

using namespace std;

OutputThread::OutputThread( string name ) {
    this->name = name;
    this->finishFlag = false;
    this->bufferLen = 0;
}

void OutputThread::run( FILE* pipe ) {
    char ch;
    while( ( ch = fgetc( pipe ) ) != EOF ) {
        {
            std::lock_guard<std::mutex> lock( mtx );
            buffer << ch;     
            bufferLen++;
        }
    }

    this->finish();
}

void OutputThread::finish() {
    std::lock_guard<std::mutex> lock( mtx );

    finishFlag = true;    
}

bool OutputThread::hasNextOutput() {
    std::lock_guard<std::mutex> lock( mtx );

    return bufferLen > 0;
}

string OutputThread::nextOutput(){
    std::lock_guard<std::mutex> lock( mtx );

    string str = buffer.str();
    buffer.str("");
    bufferLen = 0;
    return str;
}

string OutputThread::getName() {
    return name;
}

bool OutputThread::isFinished() {
    std::lock_guard<std::mutex> lock( mtx );

    return finishFlag;
}