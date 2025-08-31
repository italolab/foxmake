
#include "OutputController.h"

#include <iostream>

using std::cout;

/*
Essa classe gerencia a impressão de texto de todos os processos iniciados 
concorrentemente. É lida a saída de cada processo em sequência. Porêm, a leitura 
do buffer da classe OutputThread pode coincidir de acontecer ao mesmo tempo que 
OutputThread está inserindo caracteres no buffer.
*/

OutputController::OutputController( Output* out, bool showOutputFlag ) {
    this->out = out;
    this->showOutputFlag = showOutputFlag;
}

void OutputController::run() {
    for( OutputThread* outputThread : outputThreadVect ) { 
        while( !outputThread->isFinished() || outputThread->hasNextOutput() ) {
            if ( outputThread->hasNextOutput() ) {
                string output = outputThread->nextOutput();
                if ( showOutputFlag )
                    *out << output << std::flush;
            } else {
                std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
            }
        }
    }
}

void OutputController::finish() {
    for( OutputThread* outputThread : outputThreadVect )        
        outputThread->finish();    
}

void OutputController::addOutputThread( OutputThread* outputThread ) {
    outputThreadVect.push_back( outputThread );
}