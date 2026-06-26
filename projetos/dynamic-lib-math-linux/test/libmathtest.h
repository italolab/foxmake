#include <xutest/xutest.h>

#include "libmath.h"

TEST_CASE( fatorialTest, libmathTest ) {
    ASSERT_EQUALS( libmath::fatorial( 5 ), 120, )
}