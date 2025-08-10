
#include "TestesGrupo.h"
#include "teste_error.h"

#include <sstream>

TestesGrupo::TestesGrupo( string nome ) {
    this->nome = nome;
}

void TestesGrupo::add( string nome, function<void()> f ) {
    TesteFunc func;
    func.nome = nome;
    func.f = f;
    funcs.push_back( func );
}

int TestesGrupo::getQuantTestes() {
    return funcs.size();
}

vector<string> TestesGrupo::testeFuncNomes() {
    vector<string> fnomes;

    int tam = funcs.size();
    for( int i = 0; i < tam; i++ ) {
        string fnome = funcs[ i ].nome;
        if ( fnome.length() > 0 )
            fnome[ 0 ] = toupper( fnome[ 0 ] );

        fnomes.push_back( nome + fnome );
    }
    return fnomes;
}

TestesResult* TestesGrupo::executa() {
    int errosCont = 0;

    stringstream ss;

    ss << "Executando ( " << nome << " testes )" << endl;

    int tam = funcs.size();
    for( int i = 0; i < tam; i++ ) {
        ss << "\t" << funcs[i].nome << " - ";

        bool result;
        string error;
        try {
            funcs[ i ].f();
            result = true;
        } catch ( const teste_error& e ) {
            error = e.what();
            result = false;
            errosCont++;
        } catch ( const exception& e ) {
            error = e.what();
            result = false;
            errosCont++;
        } catch ( ... ) {
            error = "Erro desconhecido!";
            result = false;
            errosCont++;
        }

        if ( result ) {
            ss << "Ok" << endl;
        } else {
            ss << "Falha" << endl;
            ss << "\nErro: " << error << endl << endl;
        }
    }
    ss << endl;

    return new TestesResult( ss.str(), errosCont );
}

TestesResult* TestesGrupo::executaTeste( int testeIndice ) {
    int tam = funcs.size();
    stringstream ss;

    if ( testeIndice < 0 || testeIndice > tam ) {
        ss << "Ha " << tam << " testes. Indice de teste igual a " << testeIndice << "." << endl;
        return new TestesResult( ss.str(), 1 );
    }


    int errosCont = 0;

    string fnome = funcs[ testeIndice ].nome;
    if ( fnome.length() > 0 )
        fnome[ 0 ] = toupper( fnome[ 0 ] );

    fnome = nome + fnome;

    ss << "Executando teste... ( " << fnome << " ) - ";

    string error;
    try {
        funcs[ testeIndice ].f();
        errosCont = 0;
    } catch ( const teste_error& e ) {
        error = e.what();
        errosCont = 1;
    } catch ( const exception& e ) {
        error = e.what();
        errosCont = 1;
    } catch ( ... ) {
        error = "Erro desconhecido!";
        errosCont = 1;
    }

    if ( errosCont == 0 ) {
        ss << "Ok" << endl;
    } else {
        ss << "Falha" << endl;
        ss << "\nErro: " << error << endl << endl;
    }
    ss << endl;

    return new TestesResult( ss.str(), errosCont );
}
