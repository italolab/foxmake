#ifndef TESTES_UTIL_H
#define TESTES_UTIL_H

#if BUILD_DLL
#define TESTES_UTIL_API __declspec(dllexport)
#else
#define TESTES_UTIL_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>

using namespace std;

namespace testesunit {

    TESTES_UTIL_API void deveSerVerdade( bool, string msg = "" );

    TESTES_UTIL_API void deveSerFalso( bool, string msg = "" );

    TESTES_UTIL_API void deveSerNulo( void*, string msg = "" );

    TESTES_UTIL_API void deveSerNaoNulo( void*, string msg = "" );


    TESTES_UTIL_API void devemSerIguais( void*, void*, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( int, int, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( double, double, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( float, float, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( string, string, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( int*, int*, int, string msg = "" );

    TESTES_UTIL_API void devemSerIguais( vector<int>, vector<int>, string msg = "" );


    TESTES_UTIL_API void devemSerDiferentes( void*, void*, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( int, int, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( double, double, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( float, float, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( string, string, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( int*, int*, int, string msg = "" );

    TESTES_UTIL_API void devemSerDiferentes( vector<int>, vector<int>, string msg = "" );

}

#endif
