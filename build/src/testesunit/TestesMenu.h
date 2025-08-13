#ifndef TESTES_MENU_H
#define TESTES_MENU_H

#if BUILD_DLL
#define TESTES_MENU_API __declspec(dllexport)
#else
#define TESTES_MENU_API __declspec(dllimport)
#endif

#include "Testes.h"

#include <iostream>
#include <vector>

using namespace std;

class TESTES_MENU_API TestesMenu {

    private:
        Testes* testes;

        void mostraMenu( vector<string> fnomes );
        int leOpcao( int quantTestes );

    public:
        TestesMenu( Testes* testes );
        void executa();

};

#endif
