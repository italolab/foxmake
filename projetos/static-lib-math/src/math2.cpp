#include "math2.h"


int math2::fat( int n ) {
    if ( n <= 1 )
        return 1;
    return n * fat( n-1 );
}

int math2::fibo( int n ) {
    if ( n <= 2 )
        return 1;
    return fibo( n-1 ) + fibo( n-2 );
}