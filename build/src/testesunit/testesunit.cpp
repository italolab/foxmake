
#include "testesunit.h"
#include "teste_error.h"

#include <iostream>
#include <optional>
#include <vector>
#include <sstream>

namespace testesunit2 {

    void deveSerVerdade2( bool, string );

    void deveSerFalso2( bool, string );

    void deveSerNulo2( void*, string );

    void deveSerNaoNulo2( void*, string );


    template <typename T>
    void devemSerIguais2( void*, void*, string );

    template <typename T>
    void devemSerIguais2( T, T, string );

    template <typename T>
    void devemSerIguais2( T*, T*, int, string );

    template <typename T>
    void devemSerIguais2( vector<T>, vector<T>, string );


    template <typename T>
    void devemSerDiferentes2( void*, void*, string );

    template <typename T>
    void devemSerDiferentes2( T, T, string );

    template <typename T>
    void devemSerDiferentes2( T*, T*, int, string );

    template <typename T>
    void devemSerDiferentes2( vector<T>, vector<T>, string );

}

namespace testesunit {

    using namespace testesunit2;

    TESTES_UTIL_API void deveSerVerdade( bool condicao, string msg ) {
        deveSerVerdade2( condicao, msg );
    }

    TESTES_UTIL_API void deveSerFalso( bool condicao, string msg ) {
        deveSerFalso2( condicao, msg );
    }

    TESTES_UTIL_API void deveSerNulo( void* ptr, string msg ) {
        deveSerNulo2( ptr, msg );
    }

    TESTES_UTIL_API void deveSerNaoNulo( void* ptr, string msg ) {
        deveSerNaoNulo2( ptr, msg );
    }


    TESTES_UTIL_API void devemSerIguais( void* p1, void* p2, string msg ) {
        devemSerIguais2( p1, p2, msg );
    }

    TESTES_UTIL_API void devemSerIguais( int n1, int n2, string msg ) {
        devemSerIguais2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerIguais( double n1, double n2, string msg ) {
        devemSerIguais2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerIguais( float n1, float n2, string msg ) {
        devemSerIguais2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerIguais( string s1, string s2, string msg ) {
        devemSerIguais2( s1, s2, msg );
    }

    TESTES_UTIL_API void devemSerIguais( int* v1, int* v2, int tam, string msg ) {
        devemSerIguais2( v1, v2, tam, msg );
    }

    TESTES_UTIL_API void devemSerIguais( vector<int> v1, vector<int> v2, string msg ) {
        devemSerIguais2( v1, v2, msg );
    }


    TESTES_UTIL_API void devemSerDiferentes( void* p1, void* p2, string msg ) {
        devemSerDiferentes2( p1, p2, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( int n1, int n2, string msg ) {
        devemSerDiferentes2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( double n1, double n2, string msg ) {
        devemSerDiferentes2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( float n1, float n2, string msg ) {
        devemSerDiferentes2( n1, n2, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( string s1, string s2, string msg ) {
        devemSerDiferentes2( s1, s2, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( int* v1, int* v2, int tam, string msg ) {
        devemSerDiferentes2( v1, v2, tam, msg );
    }

    TESTES_UTIL_API void devemSerDiferentes( vector<int> v1, vector<int> v2, string msg ) {
        devemSerDiferentes2( v1, v2, msg );
    }

}

namespace testesunit2 {

    template <typename T>
    string stringValores( string, T, T );

    template <typename T>
    string stringVetores( string, T*, T*, int );

    template <typename T>
    string stringVetores( string, vector<T>, vector<T> );


    void deveSerVerdade2( bool condicao, string msg ) {
        if ( !condicao ) {
            string error;
            if ( msg == "" )
                error = "Deveria ser verdade.";
            else error = msg;
            throw teste_error( error );
        }
    }

    void deveSerFalso2( bool condicao, string msg ) {
        if ( condicao ) {
            string error;
            if ( msg == "" )
                error = "Deveria ser falso.";
            else error = msg;
            throw teste_error( error );
        }
    }

    void deveSerNulo2( void* ptr, string msg ) {
        if(  ptr != nullptr ) {
            string error;
            if ( msg == "" )
                error = "Ponteiro não nulo.";
            else error = msg;
            throw teste_error( error );
        }
    }

    void deveSerNaoNulo2( void* ptr, string msg ) {
        if(  ptr == nullptr ) {
            string error;
            if ( msg == "" )
                error = "Ponteiro nulo.";
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerIguais2( void* p1, void* p2, string msg ) {
        if ( p1 != p2 ) {
            string error;
            if ( msg == "" )
                error = "Ponteiros diferentes.";
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerIguais2( T v1, T v2, string msg ) {
        if ( v1 != v2 ) {
            string error;
            if ( msg == "" )
                error = stringValores( "Valores diferentes -> ", v1, v2 );
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerIguais2( T* v1, T* v2, int tam, string msg ) {
        bool iguais = true;
        for( int i = 0; iguais && i < tam; i++ )
            if ( v1[ i ] != v2[ i ] )
                iguais = false;

        if ( !iguais ) {
            string error;
            if ( msg == "" )
                error = stringVetores( "diferentes", v1, v2, tam );
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerIguais2( vector<T> v1, vector<T> v2, string msg ) {
        int tam = v1.size();

        bool iguais = v1.size() == v2.size();
        for( int i = 0; iguais && i < tam; i++ )
            if ( v1[ i ] != v2[ i ] )
                iguais = false;

        if ( !iguais ) {
            string error;
            if ( msg == "" )
                error = stringVetores( "diferentes", v1, v2 );
            else error = msg;
            throw teste_error( error );
        }
    }


    template <typename T>
    void devemSerDiferentes2( void* p1, void* p2, string msg ) {
        if ( p1 == p2 ) {
            string error;
            if ( msg == "" )
                error = "Ponteiros iguais.";
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerDiferentes2( T v1, T v2, string msg ) {
        if ( v1 == v2 ) {
            string error;
            if ( msg == "" )
                error = stringValores( "Valores iguais - >", v1, v2 );
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerDiferentes2( T* v1, T* v2, int tam, string msg ) {
        bool diferentes = true;
        for( int i = 0; diferentes && i < tam; i++ )
            if ( v1[ i ] == v2[ i ] )
                diferentes = false;

        if ( !diferentes ) {
            string error;
            if ( msg == "" )
                error = stringVetores( "iguais", v1, v2, tam );
            else error = msg;
            throw teste_error( error );
        }
    }

    template <typename T>
    void devemSerDiferentes2( vector<T> v1, vector<T> v2, string msg ) {
        int tam = v1.size();

        bool diferentes = true;
        if ( v1.size() == v2.size() ) {
            for( int i = 0; diferentes && i < tam; i++ )
                if ( v1[ i ] == v2[ i ] )
                    diferentes = false;
        }

        if ( !diferentes ) {
            string error;
            if ( msg == "" )
                error = stringVetores( "iguais", v1, v2 );
            else error = msg;
            throw teste_error( error );
        }
    }


    template <typename T>
    string stringValores( string msg, T v1, T v2 ) {
        stringstream v1ss;
        v1ss << v1;
        stringstream v2ss;
        v2ss << v2;

        return msg + v1ss.str() + " e " + v2ss.str();
    }

    template <typename T>
    string stringVetores( string message, T* v1, T* v2, int tam ) {
        string msg = " " + message;

        msg += "\nVetor(1)= ";
        for( int i = 0; i < tam; i++ )
            msg += v1[ i ] + " ";
        msg += "\nVetor(2)= ";
        for( int i = 0; i < tam; i++ )
            msg += v2[ i ] + " ";

        return msg;
    }

    template <typename T>
    string stringVetores( string message, vector<T> v1, vector<T> v2 ) {
        string msg = " " + message;

        msg += "\nVetor(1)= ";
        for( int i = 0; i < (int)v1.size(); i++ ) {
            stringstream ss;
            ss << v1[ i ];
            msg += ss.str() + " ";
        }
        msg += "\nVetor(2)= ";
        for( int i = 0; i < (int)v2.size(); i++ ) {
            stringstream ss;
            ss << v2[ i ];
            msg += ss.str() + " ";
        }

        return msg;
    }

}
