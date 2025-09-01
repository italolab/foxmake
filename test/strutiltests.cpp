
#include "strutiltests.h"
#include <util/strutil.h>

#include <test/cbtest.h>

#include <vector>

using std::vector;

TEST_CASE( startsWithTest, strutil ) {
    ASSERT_TRUE( strutil::startsWith( "abc", "a" ), );
    ASSERT_TRUE( strutil::startsWith( "_abc", "_" ), );
    ASSERT_TRUE( strutil::startsWith( "(", "(" ), );
	ASSERT_FALSE( strutil::startsWith( "abc", "bc" ), );
	ASSERT_FALSE( strutil::startsWith( "", "bc" ), );
	ASSERT_FALSE( strutil::startsWith( "", "AB" ), );
	ASSERT_TRUE( strutil::startsWith( "", "" ), );
}

TEST_CASE( endsWithTest, strutil ) {
    ASSERT_TRUE( strutil::endsWith( "abc", "bc" ), );
    ASSERT_TRUE( strutil::endsWith( "abc*.txt", ".txt" ), );
    ASSERT_TRUE( strutil::endsWith( "a", "a" ), );
    ASSERT_TRUE( strutil::endsWith( "", "" ), );
    ASSERT_TRUE( strutil::endsWith( "aaa", "" ), );

    ASSERT_FALSE( strutil::endsWith( "abc", "ac" ), );
    ASSERT_FALSE( strutil::endsWith( "abc*.txt", "txx" ), );
    ASSERT_FALSE( strutil::endsWith( "", "a" ), );
    ASSERT_FALSE( strutil::endsWith( "a", "ab" ), );
}

TEST_CASE( endsWithSomeTest, strutil ) {
    ASSERT_TRUE( strutil::endsWithSome( "abc.cpp", ".cc .cpp .c" ), );
    ASSERT_TRUE( strutil::endsWithSome( "abc.cpp", ".cpp .c .cc" ), );
    ASSERT_TRUE( strutil::endsWithSome( "abc.cpp", ".cc .c .cpp" ), );
    ASSERT_TRUE( strutil::endsWithSome( "abc.cpp", "  .cc    .cpp  .c   " ), );

    ASSERT_FALSE( strutil::endsWithSome( "abc.cpp", "" ), );
    ASSERT_FALSE( strutil::endsWithSome( "abc.cpp", ".cc .tpp .h .c" ), );
}

TEST_CASE( isEqualToSomeTest, strutil ) {
    ASSERT_TRUE( strutil::isEqualToSome( "abc", "a ab abc cba" ), ); 
    ASSERT_TRUE( strutil::isEqualToSome( "abc", " a   ab  abc  cba  " ), ); 
    ASSERT_FALSE( strutil::isEqualToSome( "abc", "a ab cba" ), ); 
    ASSERT_FALSE( strutil::isEqualToSome( "abc", "" ), ); 
}

TEST_CASE( isNextSubstrTest, strutil ) {
    ASSERT_TRUE( strutil::isNextSubstr( "abc def", 4, "def" ), );
    ASSERT_TRUE( strutil::isNextSubstr( "   abc   def  ", 9, "def" ), );
    
    ASSERT_FALSE( strutil::isNextSubstr( "abc    def ghi", 5, "def" ), );
    ASSERT_FALSE( strutil::isNextSubstr( "abc    def ghi", 4, "def" ), );
    ASSERT_FALSE( strutil::isNextSubstr( "abc    def ghi", 4, "deg" ), );
    ASSERT_FALSE( strutil::isNextSubstr( "abc    def ghi", -1, "def" ), );
    ASSERT_FALSE( strutil::isNextSubstr( "abc    def ghi", 20, "def" ), );
}

TEST_CASE( trimTests, strutil ) {
    ASSERT_EQUALS( strutil::trim( "  abc  " ), "abc", );
    ASSERT_EQUALS( strutil::trim( "abc" ), "abc", );
    ASSERT_EQUALS( strutil::trim( "" ), "", );

    ASSERT_NOT_EQUALS( strutil::trim( "abc" ), "abd", );
    ASSERT_NOT_EQUALS( strutil::trim( "  abc  " ), "abd", );
    ASSERT_NOT_EQUALS( strutil::trim( "  abc  " ), "", );
    ASSERT_NOT_EQUALS( strutil::trim( "" ), "a", );
    ASSERT_NOT_EQUALS( strutil::trim( "a" ), "", );
}

TEST_CASE( replaceTest, strutil ) {
    ASSERT_EQUALS( strutil::replace( "abcde", "bc", "" ), "ade", );
    ASSERT_EQUALS( strutil::replace( "  abc de  ", " ", "X" ), "X abc de  ", );
    ASSERT_EQUALS( strutil::replace( "abcde ", " ", "X" ), "abcdeX", );
    ASSERT_EQUALS( strutil::replace( "abcde ", "bb", "" ), "abcde ", );

    ASSERT_NOT_EQUALS( strutil::replace( "abcde ", " ", "X" ), "abcde ", );
    ASSERT_NOT_EQUALS( strutil::replace( "abcde ", "bc", "" ), "abcde ", );
}

TEST_CASE( replaceAllTest, strutil ) {
    ASSERT_EQUALS( strutil::replaceAll( "abcde", "bc", "" ), "ade", );
    ASSERT_EQUALS( strutil::replaceAll( "  abc de  ", " ", "X" ), "XXabcXdeXX", );
    ASSERT_EQUALS( strutil::replaceAll( "abcde ", " ", "X" ), "abcdeX", );
    ASSERT_EQUALS( strutil::replaceAll( "abcde ", "bb", "" ), "abcde ", );

    ASSERT_NOT_EQUALS( strutil::replaceAll( "abcde ", " ", "X" ), "abcde ", );
    ASSERT_NOT_EQUALS( strutil::replaceAll( "abcde ", "bc", "" ), "abcde ", );
    ASSERT_NOT_EQUALS( strutil::replaceAll( "  abc de  ", " ", "X" ), "XXabcXdeX ", );
}

TEST_CASE( isWhiteSpaceTest, strutil ) {
    ASSERT_TRUE( strutil::isWhiteSpace( ' ' ), );
    ASSERT_TRUE( strutil::isWhiteSpace( '\n' ), );
    ASSERT_TRUE( strutil::isWhiteSpace( '\t' ), );
    ASSERT_TRUE( strutil::isWhiteSpace( '\r' ), );

    ASSERT_FALSE( strutil::isWhiteSpace( 'a' ), );
    ASSERT_FALSE( strutil::isWhiteSpace( '\0' ), );
    ASSERT_FALSE( strutil::isWhiteSpace( '\\' ), );
}

TEST_CASE( removeStartWithSpacesTest, strutil ) {
    ASSERT_EQUALS( strutil::removeStartWhiteSpaces( "  abc" ), "abc", );
    ASSERT_EQUALS( strutil::removeStartWhiteSpaces( "abc" ), "abc", );
    ASSERT_EQUALS( strutil::removeStartWhiteSpaces( "\n\t \t \rabc" ), "abc", );
    ASSERT_EQUALS( strutil::removeStartWhiteSpaces( "\n\tX\t \rabc" ), "X\t \rabc", );
    ASSERT_EQUALS( strutil::removeStartWhiteSpaces( "" ), "", );

    ASSERT_NOT_EQUALS( strutil::removeStartWhiteSpaces( "\n\tX\t \rabc" ), "abc", );
    ASSERT_NOT_EQUALS( strutil::removeStartWhiteSpaces( "\n\tX\t \rabc" ), "\n\tX\t \rabc", );
}

TEST_CASE( splitWithDoubleQuotesTest, strutil ) {
    string str1 = "   a b c  ";
    vector<string> split1 = { "a", "b", "c" };

    string str2 = " \n\t\r  \"a=b\" \t \"c\" d \"--e=f g/g\" g  ";
    vector<string> split2 = { "a=b", "c", "d", "--e=f g/g", "g" };

    string str3 = "  \t\r \n ";
    vector<string> split3 = {};

    string str4 = "";
    vector<string> split4 = {};

    ASSERT_EQUALS_VECTORS( strutil::splitWithDoubleQuotes( str1 ), split1, );
    ASSERT_EQUALS_VECTORS( strutil::splitWithDoubleQuotes( str2 ), split2, );
    ASSERT_EQUALS_VECTORS( strutil::splitWithDoubleQuotes( str3 ), split3, );
    ASSERT_EQUALS_VECTORS( strutil::splitWithDoubleQuotes( str4 ), split4, );

    string str5 = "a \"b c\" d";
    vector<string> split5 = { "a", "b", "c", "d" };

    ASSERT_NOT_EQUALS_VECTORS( strutil::splitWithDoubleQuotes( str5 ), split5, );
}

namespace strutiltests {
    
    void addTestCases() {
        ADD_TEST_CASE( startsWithTest, strutil );
        ADD_TEST_CASE( endsWithTest, strutil );
        ADD_TEST_CASE( endsWithSomeTest, strutil );
        ADD_TEST_CASE( isEqualToSomeTest, strutil );
        ADD_TEST_CASE( isNextSubstrTest, strutil );
        ADD_TEST_CASE( trimTests, strutil );
        ADD_TEST_CASE( replaceTest, strutil );
        ADD_TEST_CASE( replaceAllTest, strutil );
        ADD_TEST_CASE( isWhiteSpaceTest, strutil );
        ADD_TEST_CASE( removeStartWithSpacesTest, strutil );
        ADD_TEST_CASE( splitWithDoubleQuotesTest, strutil );
    }
    
}