#include <xutest/xutest.h>

#include "math2.h"

TEST_CASE( fatorialTest, math2Test ) {
    ASSERT_EQUALS( math2::fat( 0 ), 1, );
    ASSERT_EQUALS( math2::fat( 1 ), 1, );
    ASSERT_EQUALS( math2::fat( 2 ), 2, );
    ASSERT_EQUALS( math2::fat( 3 ), 6, );
    ASSERT_EQUALS( math2::fat( 5 ), 120, );
}

TEST_CASE( fibbonacciTest, math2Test ) {
    ASSERT_EQUALS( math2::fibo( 0 ), 1, );
    ASSERT_EQUALS( math2::fibo( 1 ), 1, );
    ASSERT_EQUALS( math2::fibo( 2 ), 1, );
    ASSERT_EQUALS( math2::fibo( 3 ), 2, );
    ASSERT_EQUALS( math2::fibo( 4 ), 3, );
    ASSERT_EQUALS( math2::fibo( 5 ), 5, );
    ASSERT_EQUALS( math2::fibo( 6 ), 8, );
    ASSERT_EQUALS( math2::fibo( 7 ), 13, );
}