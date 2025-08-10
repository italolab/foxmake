
#include "TestesResult.h"

TestesResult::TestesResult( string msg, int quantErros ) {
    this->msg = msg;
    this->quantErros = quantErros;
}

string TestesResult::getMensagem() {
    return msg;
}

int TestesResult::getQuantErros() {
    return quantErros;
}
