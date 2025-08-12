#ifndef TESTE_ERROR_H
#define TESTE_ERROR_H

#if BUILD_DLL
#define TESTE_ERROR_API __declspec(dllexport)
#else
#define TESTE_ERROR_API __declspec(dllimport)
#endif

#include <stdexcept>
#include <iostream>

using namespace std;

class TESTE_ERROR_API teste_error : public runtime_error {

    public:
        teste_error( string msg );

};

#endif
