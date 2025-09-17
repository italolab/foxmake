
#include "OutputController.h"

#include <iostream>

/*
Essa classe gerencia a impressão de texto de todos os processos iniciados 
concorrentemente. É lida a saída de cada processo em sequência. Porêm, a leitura 
do buffer da classe OutputThread pode coincidir de acontecer ao mesmo tempo que 
OutputThread está inserindo caracteres no buffer.
*/

OutputController::OutputController( Shell* shell ) {
    this->shell = shell;
    this->isFinish = false;
}

void OutputController::run() {
    Output out = *( shell->getOutput() );
    bool isVerbose = shell->isVerbose();
    bool isShowOutput = shell->isShowOutput();

    this->isFinish = false;

    while( !isFinish ) { 
        OutputThread* outputThread = nullptr;
        if ( !outputThreadVect.empty() )
            outputThread = outputThreadVect.front();

        if ( outputThread == nullptr ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
            continue;
        }

        outputThreadVect.erase( outputThreadVect.begin() + 0 );

        if ( isVerbose )
            out << outputThread->getCMDStr() << std::endl;   
            
        while( !outputThread->isFinished() || outputThread->hasNextOutput() ) {
            if ( outputThread->hasNextOutput() ) {
                string output = outputThread->nextOutput();
                if ( isShowOutput )
                    out << output << std::flush;
            } else {
                std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
            }
        }        
    }
}

void OutputController::finish() {
    for( OutputThread* outputThread : outputThreadVect )        
        outputThread->finish();   
    this->isFinish = true; 
}

void OutputController::addOutputThread( OutputThread* outputThread ) {
    outputThreadVect.push_back( outputThread );
}