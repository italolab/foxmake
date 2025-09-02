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
    ASSERT_EQUALS( io::path::dirPath( "/" ), "/", );
    ASSERT_EQUALS( io::path::dirPath( "" ), "", );
}

TEST_CASE( recursiveDirPathTest, IOTests ) {
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "a/**/b/c" ), "a/b", );
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "a/b/c/**/" ), "a/b", );
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "**/a/b/c" ), "a/b", );
    ASSERT_NOT_EQUALS( io::path::jokerJokerDirPath( "a/b/c/**" ), "a/b", );
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "" ), "", );
}

TEST_CASE( recursiveDirPathToReplaceTest, IOTests ) {
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "a/b/**/c/d" ), "a/b/",  );
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "**/a/b/c" ), "",  );
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "/**/a/b/c" ), "/",  );
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "/a/**/b/c" ), "/a/",  );
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "" ), "",  );
}

TEST_CASE( fileOrDirNameTest, IOTests ) {
    ASSERT_EQUALS( io::path::fileOrDirName( "a" ), "a", );
    ASSERT_EQUALS( io::path::fileOrDirName( "a/a/b" ), "b", );
    ASSERT_EQUALS( io::path::fileOrDirName( "a/a/b.txt" ), "b.txt", );
    ASSERT_EQUALS( io::path::fileOrDirName( "/*.txt" ), "*.txt", );
    ASSERT_EQUALS( io::path::fileOrDirName( "/*a*.*" ), "*a*.*", );
    ASSERT_EQUALS( io::path::fileOrDirName( "" ), "", );
}

TEST_CASE( fileOrDirNameWithoutExtensionTest, IOTests ) {
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a" ), "a", );
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a/a/b" ), "b", );
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a/a/b.txt" ), "b", );
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "/*" ), "*", );
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "/*a*" ), "*a*", );
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "" ), "", );
}

TEST_CASE( makeUnixPreferredTest, IOTests ) {
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:\\a\\b" ), "C:/a/b", );
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:" ), "C:", );
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:\\a/b/c\\d" ), "C:/a/b/c/d", );
    ASSERT_EQUALS( io::path::makeUnixPreferred( "a\\b/c\\d" ), "a/b/c/d", );
    ASSERT_EQUALS( io::path::makeUnixPreferred( "" ), "", );
}

TEST_CASE( addSeparatorIfNeedTest, IOTests ) {
    ASSERT_EQUALS( io::path::addSeparatorToDirIfNeed( "/a/b" ), "/a/b/", );
    ASSERT_EQUALS( io::path::addSeparatorToDirIfNeed( "/a/b/" ), "/a/b/", );
    ASSERT_EQUALS( io::path::addSeparatorToDirIfNeed( "/" ), "/", );
    ASSERT_EQUALS( io::path::addSeparatorToDirIfNeed( "" ), "", );
}

TEST_CASE( removeSeparatorIfNeedTest, IOTests ) {
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/a/b" ), "/a/b", );
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/a/b/" ), "/a/b", );
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/" ), "/", );
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "" ), "", );
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