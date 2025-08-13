#ifndef TESTES_H
#define TESTES_H

#if BUILD_DLL
#define TESTES_API __declspec(dllexport)
#else
#define TESTES_API __declspec(dllimport)
#endif

#include "TestesResult.h"

#include <functional>
#include <vector>

class TESTES_API Testes {

    public:
        virtual vector<string> testeFuncNomes() = 0;
        virtual TestesResult* executaTeste( int testeIndice ) = 0;
        virtual TestesResult* executa() = 0;

};

#endif
