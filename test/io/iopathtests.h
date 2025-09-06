#ifndef IO_TESTS_H
#define IO_TESTS_H

#include <io/io.h>

#include <test/cbtest.h>

#include <string>

using std::string;

TEST_CASE( dirPathTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::dirPath( "C:/__xx" ), "C:", )
    ASSERT_EQUALS( io::path::dirPath( "C:__xx" ), "C:", )
    ASSERT_EQUALS( io::path::dirPath( "C:" ), "", )
    ASSERT_EQUALS( io::path::dirPath( "a/b/c" ), "a/b", )
    ASSERT_EQUALS( io::path::dirPath( "a/b/c/" ), "a/b", )
    ASSERT_EQUALS( io::path::dirPath( "/a/b" ), "/a", )
    ASSERT_EQUALS( io::path::dirPath( "/__xx" ), "/", )
    ASSERT_EQUALS( io::path::dirPath( "/" ), "/", )
    ASSERT_EQUALS( io::path::dirPath( "" ), "", )

    if ( io::fileExists( "C:/" ) )
        ASSERT_EQUALS( io::path::dirPath( "C:/" ), "C:", )
    else
        ASSERT_EQUALS( io::path::dirPath( "C:/" ), "", )       
}

TEST_CASE( recursiveDirPathToReplaceTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "a/b/**/c/d" ), "a/b/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "**/a/b/c" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "/**/a/b/c" ), "/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "/a/**/b/c" ), "/a/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "" ), "", )
}

TEST_CASE( fileOrDirNameTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::fileOrDirName( "a" ), "a", )
    ASSERT_EQUALS( io::path::fileOrDirName( "a/a/b" ), "b", )
    ASSERT_EQUALS( io::path::fileOrDirName( "a/a/b.txt" ), "b.txt", )
    ASSERT_EQUALS( io::path::fileOrDirName( "/*.txt" ), "*.txt", )
    ASSERT_EQUALS( io::path::fileOrDirName( "/*a*.*" ), "*a*.*", )
    ASSERT_EQUALS( io::path::fileOrDirName( "" ), "", )
}

TEST_CASE( fileOrDirNameWithoutExtensionTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a" ), "a", )
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a/a/b" ), "b", )
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "a/a/b.txt" ), "b", )
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "/*" ), "*", )
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "/*a*" ), "*a*", )
    ASSERT_EQUALS( io::path::fileOrDirNameWithoutExtension( "" ), "", )
}

TEST_CASE( makeUnixPreferredTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:\\a\\b" ), "C:/a/b", )
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:" ), "C:", )
    ASSERT_EQUALS( io::path::makeUnixPreferred( "C:\\a/b/c\\d" ), "C:/a/b/c/d", )
    ASSERT_EQUALS( io::path::makeUnixPreferred( "a\\b/c\\d" ), "a/b/c/d", )
    ASSERT_EQUALS( io::path::makeUnixPreferred( "" ), "", )
}

TEST_CASE( addSeparatorIfNeedTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::addSeparatorIfNeed( "/a/b" ), "/a/b/", )
    ASSERT_EQUALS( io::path::addSeparatorIfNeed( "/a/b/" ), "/a/b/", )
    ASSERT_EQUALS( io::path::addSeparatorIfNeed( "/" ), "/", )
    ASSERT_EQUALS( io::path::addSeparatorIfNeed( "" ), "", )
}

TEST_CASE( removeSeparatorIfNeedTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/a/b" ), "/a/b", )
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/a/b/" ), "/a/b", )
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "/" ), "/", )
    ASSERT_EQUALS( io::path::removeSeparatorFromDirIfNeed( "" ), "", )
}

TEST_CASE( parentPathTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::parentPath( "a/b/c" ), "a/b", )
    ASSERT_EQUALS( io::path::parentPath( "a" ), "", )
    ASSERT_EQUALS( io::path::parentPath( "/a" ), "/", )
    ASSERT_EQUALS( io::path::parentPath( "/" ), "", )
}

TEST_CASE( absolutePathTest, IOPathTests ) {
    string currpath = io::path::currentPath();

    ASSERT_EQUALS( io::path::absolutePath( "C:/a/b/c" ), "C:/a/b/c", )
    ASSERT_EQUALS( io::path::absolutePath( "/a/b/c" ), "/a/b/c", )
    ASSERT_EQUALS( io::path::absolutePath( "a/b/c" ), currpath + "/a/b/c", )

    ASSERT_EQUALS( io::path::absolutePath( "" ), currpath, )
    ASSERT_EQUALS( io::path::absolutePath( "." ), currpath, )
    ASSERT_EQUALS( io::path::absolutePath( "./" ), currpath, )
}

TEST_CASE( relativePathTest, IOPathTests ) {    
    string currpath = io::path::currentPath();

    ASSERT_EQUALS( io::path::relativePath( io::path::absolutePath( "a/b/c" ) ), "a/b/c", )
    ASSERT_EQUALS( io::path::relativePath( currpath + "/a/b/c" ), "a/b/c", )
    ASSERT_EQUALS( io::path::relativePath( currpath ), ".", )
    ASSERT_EQUALS( io::path::relativePath( currpath + "/." ), ".", )
    ASSERT_EQUALS( io::path::relativePath( currpath + "/./" ), ".", )
}

TEST_CASE( extensionTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::extension( "abc.txt" ), "txt", )
    ASSERT_EQUALS( io::path::extension( "abc.*" ), "*", )
    ASSERT_EQUALS( io::path::extension( "abc" ), "", )
    ASSERT_EQUALS( io::path::extension( "abc." ), "", )
    ASSERT_EQUALS( io::path::extension( "" ), "", )
}

TEST_CASE( jokerJokerDirPathTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "a/**/b/c" ), "a/b", )
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "a/b/c/**/" ), "a/b", )
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "**/a/b/c" ), "a/b", )
    ASSERT_EQUALS( io::path::jokerJokerDirPath( "" ), "", )
}

TEST_CASE( jokerJokerBeforePathTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "a/b/**/c/d" ), "a/b/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "**/c/d" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "a/b/**/" ), "a/b/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "a/b/**" ), "a/b/", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "**" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerBeforePath( "" ), "", )
}

TEST_CASE( jokerJokerAfterPathTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "a/b/**/c/d" ), "c/d", )
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "**/c/d" ), "c/d", )
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "a/b/**/" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "a/b/**" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "**" ), "", )
    ASSERT_EQUALS( io::path::jokerJokerAfterPath( "" ), "", )
}

TEST_CASE( removeJokerJokerTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::removeJokerJoker( "a/b/**/c/d" ), "a/b/c/d", )
    ASSERT_EQUALS( io::path::removeJokerJoker( "a/**/b" ), "a/b", )
    ASSERT_EQUALS( io::path::removeJokerJoker( "**/b" ), "b", )
    ASSERT_EQUALS( io::path::removeJokerJoker( "a/b/**" ), "a/b/", )
    ASSERT_EQUALS( io::path::removeJokerJoker( "a/b/c" ), "a/b/c", )
}

TEST_CASE( isFileNameStartsWithJoker, IOPathTests ) {
    ASSERT_TRUE( io::path::isFileNameStartsWithJoker( "a/b/*.txt" ), )
    ASSERT_TRUE( io::path::isFileNameStartsWithJoker( "a/b/*" ), )
    ASSERT_TRUE( io::path::isFileNameStartsWithJoker( "*.txt" ), )
    ASSERT_TRUE( io::path::isFileNameStartsWithJoker( "*" ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "." ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "a" ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "" ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "a/b/**/a" ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "a/b/**/" ), )
    ASSERT_FALSE( io::path::isFileNameStartsWithJoker( "**/" ), )
}

TEST_CASE( removeInitTwoDotsAndSlashesTest, IOPathTests ) {
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "../a" ), "a", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "../a/b" ), "a/b", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "../" ), "", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "../../../a" ), "a", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "../../a/b" ), "a/b", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( ".." ), "", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "" ), "", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "a/b/c" ), "a/b/c", )
    ASSERT_EQUALS( io::path::removeInitTwoDotsAndSlashes( "/a/b/" ), "/a/b/", )
}

TEST_CASE( absoluteResolvePathTest, IOPathTests ) {
    string currpath = io::path::currentPath();
    currpath = io::path::parentPath( currpath );
    currpath = io::path::parentPath( currpath );
    ASSERT_EQUALS( io::path::absoluteResolvePath( "../../d" ), currpath + "/d", )
}

TEST_CASE( resolvePathTest1, IOPathTests ) {
    ASSERT_EQUALS( io::path::resolvePath( "/a/b/c/../../d" ), "/a/d", )
    ASSERT_EQUALS( io::path::resolvePath( "/a/../../d" ), "d", )
}

TEST_CASE( resolvePathTest2, IOPathTests ) {
    ASSERT_EQUALS( io::path::resolvePath( "/a/b/c", "../../d" ), "/a/d", )
    ASSERT_EQUALS( io::path::resolvePath( "/a/", "../../d" ), "d", )
}

#endif