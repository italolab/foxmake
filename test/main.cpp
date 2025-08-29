#include <test/cbtest.h>

#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;
using std::runtime_error;

class X {

};

TEST_CASE( test0, ) {
    ASSERT_EQUALS( 0, 1, Houve erro... );
}

TEST_CASE( test1, classes ) {
	ASSERT_EQUALS( 1, 1, );
	ASSERT_EQUALS( 2, 2, );

	ASSERT_TRUE( true, );
	ASSERT_FALSE( false, );

	ASSERT_NULL( nullptr, );
	ASSERT_NOT_NULL( new string, );

	int a1[] = { 1, 2, 3 };
	int a2[] = { 1, 2, 3 };
	int a3[] = { 1, 2, 4, 4 };

	X* x1 = new X;
	X* x2 = new X;
	X* x3 = new X;

	vector<X*> v1 = { x1, x2, x3 };
	vector<X*> v2 = { x1, x2, x3 };
	vector<X*> v3 = { x1, x2, x3, new X };

	ASSERT_EQUALS_ARRAYS( a1, a2, 3, abc );
	ASSERT_NOT_EQUALS_ARRAYS( a1, a3, 3, abcd );

	ASSERT_EQUALS_VECTORS( v1, v2, );
	ASSERT_NOT_EQUALS_VECTORS( v1, v3, );

	ASSERT_EQUALS_VECTORS( v1, v2, );
	ASSERT_NOT_EQUALS_VECTORS( v1, v2, );
}

TEST_CASE( teste3, classes ) {
	ASSERT_THROWS( runtime_error, {
		if ( 1 == 2 )
			throw runtime_error( "erro!" );
	}, );
}

int main() {
	ADD_TEST_CASE( test1, classes );
    ADD_TEST_CASE( test0, );
	ADD_TEST_CASE( teste3, classes );

	RUN_TEST_CASES_MENU();
}
