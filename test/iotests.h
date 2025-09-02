#ifndef IO_TESTS_H
#define IO_TESTS_H

#include "io/io.h"

#include <test/cbtest.h>

#include <string>

#include <iostream>
using namespace std;

using std::string;

TEST_CASE( makePreferredTest, IOTests ) {
    ASSERT_EQUALS( io::path::makePreferred( "a/b/c" ), "a/b/c", );
    ASSERT_EQUALS( io::path::makePreferred( "/a/b/c/" ), "/a/b/c/", );
}

TEST_CASE( dirPathTest, IOTests ) {
    ASSERT_EQUALS( io::path::dirPath( "C:/__xx" ), "C:", );
    ASSERT_EQUALS( io::path::dirPath( "C:__xx" ), "C:", );
    ASSERT_EQUALS( io::path::dirPath( "C:" ), "", );
    ASSERT_EQUALS( io::path::dirPath( "C:/" ), "", );
    ASSERT_EQUALS( io::path::dirPath( "a/b/c" ), "a/b", );
    ASSERT_EQUALS( io::path::dirPath( "a/b/c/" ), "a/b", );
    ASSERT_EQUALS( io::path::dirPath( "/a/b" ), "/a", );
    ASSERT_EQUALS( io::path::dirPath( "/__xx" ), "/", );
    ASSERT_EQUALS( io::path::dirPath( "/" ), "", );
    ASSERT_EQUALS( io::path::dirPath( "" ), "", );
}

TEST_CASE( recursiveDirPathTest, IOTests ) {
    ASSERT_EQUALS( io::path::recursiveDirPath( "a/**/b/c" ), "a/b", );
    ASSERT_EQUALS( io::path::recursiveDirPath( "a/b/c/**/" ), "a/b", );
    ASSERT_EQUALS( io::path::recursiveDirPath( "**/a/b/c" ), "a/b", );
    ASSERT_NOT_EQUALS( io::path::recursiveDirPath( "a/b/c/**" ), "a/b", );
    ASSERT_EQUALS( io::path::recursiveDirPath( "" ), "", );
}

TEST_CASE( recursiveDirPathToReplaceTest, IOTests ) {
    ASSERT_EQUALS( io::path::recursiveDirPathToReplace( "a/b/**/c/d" ), "a/b/",  );
    ASSERT_EQUALS( io::path::recursiveDirPathToReplace( "**/a/b/c" ), "",  );
    ASSERT_EQUALS( io::path::recursiveDirPathToReplace( "/**/a/b/c" ), "/",  );
    ASSERT_EQUALS( io::path::recursiveDirPathToReplace( "/a/**/b/c" ), "/a/",  );
    ASSERT_EQUALS( io::path::recursiveDirPathToReplace( "" ), "",  );
}

TEST_CASE( absolutePathTest, IOTests ) {
    string currpath = io::path::currentPath();

    ASSERT_EQUALS( io::path::absolutePath( "C:/a/b/c" ), "C:/a/b/c", );
    ASSERT_EQUALS( io::path::absolutePath( "/a/b/c" ), "/a/b/c", );
    ASSERT_EQUALS( io::path::absolutePath( "a/b/c" ), currpath + "/a/b/c", );

    ASSERT_EQUALS( io::path::absolutePath( "" ), currpath, );
    ASSERT_EQUALS( io::path::absolutePath( "." ), currpath, );
    ASSERT_EQUALS( io::path::absolutePath( "./" ), currpath, );
}

#endif