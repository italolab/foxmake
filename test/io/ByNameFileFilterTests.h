
#include <cbtest/cbtest.h>
#include <io/filter/ByNameFileFilter.h>

TEST_CASE( ByNameFileFilterTest, ByNameFileFilterTests ) {
    ByNameFileFilter* filter = new ByNameFileFilter( "*" );
    ASSERT_TRUE( filter->match( "abc" ), )
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "abc.sh" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "abc*" );
    ASSERT_TRUE( filter->match( "abc" ), )
    ASSERT_TRUE( filter->match( "abcde" ), )
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "abcde.txt" ), )
    ASSERT_FALSE( filter->match( "abde" ), )
    ASSERT_FALSE( filter->match( "ab.txt" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "abc*.*" );
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "abcde.txt" ), )
    ASSERT_FALSE( filter->match( "abc" ), )    
    ASSERT_FALSE( filter->match( "abcde" ), )
    ASSERT_FALSE( filter->match( "abde" ), )
    ASSERT_FALSE( filter->match( "ab.txt" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "*abc" );
    ASSERT_TRUE( filter->match( "xxxabc" ), )
    ASSERT_TRUE( filter->match( "xxxabc" ), )
    ASSERT_TRUE( filter->match( "abc" ), )
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "xxxabc.txt" ), )
    ASSERT_FALSE( filter->match( "xxxabd" ), )
    ASSERT_FALSE( filter->match( "xxxabd.txt" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "*abc.*" );
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "xxxabc.txt" ), )
    ASSERT_FALSE( filter->match( "abc" ), )
    ASSERT_FALSE( filter->match( "xxxabc" ), )
    ASSERT_FALSE( filter->match( "xxxabd" ), )
    ASSERT_FALSE( filter->match( "xxxabd.txt" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "abc*def" );
    ASSERT_TRUE( filter->match( "abcxxxdef" ), )
    ASSERT_TRUE( filter->match( "abcxxxdef" ), )
    ASSERT_TRUE( filter->match( "abcdef" ), )
    ASSERT_TRUE( filter->match( "abcxxxdef.txt" ), )
    ASSERT_TRUE( filter->match( "abcdef.txt" ), )
    ASSERT_FALSE( filter->match( "abcxxxdeb" ), )
    ASSERT_FALSE( filter->match( "abdxxxdef" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "abc*def.*" );
    ASSERT_TRUE( filter->match( "abcxxxdef.txt" ), )
    ASSERT_TRUE( filter->match( "abcdef.txt" ), )
    ASSERT_FALSE( filter->match( "abcxxxdef" ), )
    ASSERT_FALSE( filter->match( "abcdef" ), )
    ASSERT_FALSE( filter->match( "abcxxxdeb" ), )
    ASSERT_FALSE( filter->match( "abdxxxdef" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "*.*" );
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "abc.sh" ), )
    ASSERT_FALSE( filter->match( "abc" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "*.txt" );
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "def.txt" ), )
    ASSERT_FALSE( filter->match( "abc" ), )
    ASSERT_FALSE( filter->match( "abc.sh" ), )
    ASSERT_FALSE( filter->match( "" ), )

    filter = new ByNameFileFilter( "abc.*" );
    ASSERT_TRUE( filter->match( "abc.txt" ), )
    ASSERT_TRUE( filter->match( "abc.sh" ), )
    ASSERT_FALSE( filter->match( "abc" ), )
    ASSERT_FALSE( filter->match( "def.txt" ), )
    ASSERT_FALSE( filter->match( "" ), )
}