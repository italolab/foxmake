
#include "OutputThread.h"

#include "../CMDThreadsController.h"


#include <cstring>
#include <iostream>

/*
Esta classe mantêm um buffer de caracteres onde cada caractere lido do pipe é 
inserido. Constantemente, (e concorrentemente), o OutputController lê o conteúdo 
deste buffer e o imprime na saída padrão. 

A cada leitura, o buffer é retornado para OutputController e limpo. Isso de forma 
sincrona.
*/

OutputThread::OutputThread( void* threadsController, string name, string cmdstr ) {
    this->threadsController = threadsController;
    this->name = name;
    this->cmdstr = cmdstr;
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

    ((CMDThreadsController*)threadsController)->commandProcessedNotify();
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
string OutputThread::getCMDStr() {
    return cmdstr;
}

bool OutputThread::isFinished() {
    std::lock_guard<std::mutex> lock( mtx );

    return finishFlag;
}