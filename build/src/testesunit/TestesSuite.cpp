
#include "TestesSuite.h"

#include <sstream>

void TestesSuite::add( TestesGrupo* testes ) {
    testesVect.push_back( testes );
}

vector<string> TestesSuite::testeFuncNomes() {
    vector<string> fnomes;

    int tam = testesVect.size();
    for( int i = 0; i < tam; i++ ) {
        vector<string> vet = testesVect[ i ]->testeFuncNomes();
        fnomes.insert( fnomes.end(), vet.begin(), vet.end() );
    }

    return fnomes;
}

TestesResult* TestesSuite::executa() {
    int tam = testesVect.size();

    stringstream ss;

    int quantErros = 0;
    for( int i = 0; i < tam; i++ ) {
        TestesResult* result = testesVect[ i ]->executa();
        quantErros += result->getQuantErros();

        ss << result->getMensagem();
    }

    ss << endl;
    if ( quantErros == 0 )
        ss << "Todos os testes foram executados com sucesso." << endl;
    else ss << "Houve falha em " << quantErros << " testes." << endl;

    return new TestesResult( ss.str(), quantErros );
}

TestesResult* TestesSuite::executaTeste( int testeIndice ) {
    int cont = 0;

    int tam = testesVect.size();
    for( int i = 0; i < tam; i++ ) {
        int quant = testesVect[ i ]->getQuantTestes();
        if ( testeIndice < cont + quant ) {
            int indice = testeIndice - cont;
            return testesVect[ i ]->executaTeste( indice );
        } else {
            cont += quant;
        }
    }

    stringstream ss;
    ss << "Ha " << cont << " testes. Indice de teste igual a " << testeIndice << "." << endl;

    return new TestesResult( ss.str(), 1 );
}
