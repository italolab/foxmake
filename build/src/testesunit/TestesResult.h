#ifndef TESTES_RESULT_H
#define TESTES_RESULT_H

#if BUILD_DLL
#define TESTES_RESULT_API __declspec(dllexport)
#else
#define TESTES_RESULT_API __declspec(dllimport)
#endif

#include <string>

using namespace std;

class TESTES_RESULT_API TestesResult {

    private:
        string msg;
        int quantErros;

    public:
        TestesResult( string msg, int quantErros );
        string getMensagem();
        int getQuantErros();

};

#endif
