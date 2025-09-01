#ifndef IO_TESTS_H
#define IO_TESTS_H

#include "io/io.h"

#include <test/cbtest.h>

#include <string>

#include <iostream>
using namespace std;

using std::string;

TEST_CASE( makePreferredTest, IOTests ) {
    #ifdef _WIN32
        ASSERT_EQUALS( io::makePreferred( "a/b/b" ), "a\\b\\c", );
        ASSERT_EQUALS( io::makePreferred( "a\\b\\b" ), "a\\b\\c", );
    #else
        ASSERT_EQUALS( io::makePreferred( "a/b/c" ), "a/b/c", );
        ASSERT_EQUALS( io::makePreferred( "/a/b/c/" ), "/a/b/c/", );
    #endif
}

TEST_CASE( absolutePathTest, IOTests ) {
    string currpath = io::currentPath();

    ASSERT_EQUALS( io::absolutePath( "a/b/c" ), currpath + "/a/b/c", );
    ASSERT_EQUALS( io::absolutePath( "/a/b/c" ), "/a/b/c", );
    ASSERT_EQUALS( io::absolutePath( "" ), currpath, );
    ASSERT_EQUALS( io::absolutePath( "." ), currpath, );
    ASSERT_EQUALS( io::absolutePath( "./" ), currpath, );
}

#endif