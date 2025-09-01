#include <test/cbtest.h>

#include <util/strutil.h>

#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;
using std::runtime_error;

TEST_CASE( startsWith, strutil ) {
    ASSERT_TRUE( strutil::startsWith( "abc", "a" ), );
    ASSERT_TRUE( strutil::startsWith( "_abc", "_" ), );
    ASSERT_TRUE( strutil::startsWith( "(", "(" ), );
	ASSERT_FALSE( strutil::startsWith( "abc", "bc" ), );
	ASSERT_FALSE( strutil::startsWith( "", "bc" ), );
	ASSERT_FALSE( strutil::startsWith( "", "AB" ), );
	ASSERT_TRUE( strutil::startsWith( "", "" ), );
	//FAIL( "Falha..." );
}


int main() {
	ADD_TEST_CASE( startsWith, strutil );

	RUN_TEST_CASES_MENU();
}
