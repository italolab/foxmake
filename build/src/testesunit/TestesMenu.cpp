
#include "TestesMenu.h"

#include <sstream>
#include <limits>

TestesMenu::TestesMenu( Testes* testes ) {
    this->testes = testes;
}

void TestesMenu::executa() {
    vector<string> fnomes = testes->testeFuncNomes();
    int quantTestes = fnomes.size();

    mostraMenu( fnomes );

    int op = leOpcao( quantTestes );

    TestesResult* result;
    if ( op == 0 ) {
        result = testes->executa();
    } else {
        result = testes->executaTeste( op-1 );
    }
    cout << endl;
    cout << result->getMensagem();
}

void TestesMenu::mostraMenu( vector<string> fnomes ) {
    stringstream out;
    out << "    MENU DE TESTES" << endl;
    out << endl;
    out << " (0) Todos os testes" << endl;

    int tam = fnomes.size();
    for( int i = 0; i < tam; i++ )
         out << " (" << (i+1) << ") " << fnomes[ i ] << endl;

    cout << out.str() << endl;
}

int TestesMenu::leOpcao( int quantTestes ) {
    int op;
    string msg = "Informe o teste para rodar: ";
    string errorMsg = "Opcao invalida. Informe um valor numerico presente no menu acima!";

    cout << msg;
    bool ok;
    do {
        while( !(cin >> op) ) {
            cout << errorMsg << endl;
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
            cout << msg;
        }

        ok = true;
        if ( op < 0 || op > quantTestes ) {
            cout << "Informe um valor numerico presente no menu acima!" << endl;
            cout << msg;
            ok = false;
        }
    } while ( !ok );

    return op;
}
