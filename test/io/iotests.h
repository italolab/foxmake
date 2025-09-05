
#include <test/cbtest.h>
#include <io/io.h>

BEFORE_EACH( IOTests ) {
    io::createDir( "temp" );
    io::createDir( "temp/arquivos" );
    io::createDir( "temp/arquivos/pasta" );
    io::createDir( "temp/arquivos2" );

    io::createDir( "temp/build" );

    io::writeInTextFile( "temp/a.txt", "abc" );
    io::writeInTextFile( "temp/b.sh", "ls ." );
    io::writeInTextFile( "temp/c.bat", "dir ." );

    io::writeInTextFile( "temp/arquivos/d.txt", "ddd" );
    io::writeInTextFile( "temp/arquivos/e.sh", "ls /" );
    io::writeInTextFile( "temp/arquivos/f.bat", "ls /" );
    io::writeInTextFile( "temp/arquivos/pasta/g.txt", "ggg" );
    io::writeInTextFile( "temp/arquivos/pasta/h.txt", "hhh" );
    io::writeInTextFile( "temp/arquivos/pasta/i.txt", "iii" );

    io::writeInTextFile( "temp/arquivos2/d.txt", "ddd" );
    io::writeInTextFile( "temp/arquivos2/e.sh", "ls /" );
    io::writeInTextFile( "temp/arquivos2/f.bat", "ls /" );

    io::copyDir( "temp/arquivos", "temp/arquivos1", true, true );
}

AFTER_EACH( IOTests ) {
    io::deleteFiles( "temp", io::by_name_file_filter( "*" ), true ); 
}

TEST_CASE( copyFileTest, IOTests ) {    
    io::copyFile( "temp/b.sh", "temp/build/b.sh", true );
    io::copyFile( "temp/b.sh", "temp/build/c.sh", true );

    ASSERT_THROWS( io_error, {
        io::copyFile( "temp/x.doc", "temp/build/x.doc", true );
    }, )

    ASSERT_TRUE( io::fileExists( "temp/b.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/b.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/c.sh" ), )

    // Tenta copiar arquivo que não existe.
    ASSERT_THROWS( io_error, {
        io::copyFile( "__xxxxx", "temp/__xxxxx", true );
    }, )

    // Tenta copiar arquivo com destino que existe sem sobrescrita ativada
    ASSERT_THROWS( io_error, {
        io::copyFile( "temp/b.sh", "temp/build", false );
    }, )

    // Tenta copiar arquivo com destino que existe sem sobrescrita ativada
    ASSERT_THROWS( io_error, {
        io::copyFile( "temp/b.sh", "temp/c.bat", false );
    }, )

    io::copyFile( "temp/c.bat", "temp/build", true );
    ASSERT_TRUE( io::fileExists( "temp/c.bat" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/c.bat" ), )

    ASSERT_THROWS( io_error, {
        io::copyFile( "temp/c.bat", "temp/build", false );
    }, );
}

TEST_CASE( copyDirTest, IOTests ) {
    ASSERT_TRUE( io::fileExists( "temp/build" ), )

    ASSERT_THROWS( io_error, {
        io::copyDir( "temp/arquivos5", "temp/build", true, true );
    }, )

    ASSERT_THROWS( io_error, {
        io::copyDir( "temp/a.txt", "temp/build", true, true );
    }, )

    ASSERT_THROWS( io_error, {
        io::copyDir( "temp/arquivos", "temp/b.sh", true, true );
    }, )

    io::copyDir( "temp/arquivos", "temp/build", true, true );
    ASSERT_TRUE( io::fileExists( "temp/arquivos" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/pasta" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/f.bat" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/pasta/g.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/pasta/h.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos/pasta/i.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/pasta" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/f.bat" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/pasta/g.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/pasta/h.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/pasta/i.txt" ), )

    io::copyDir( "temp/arquivos2", "temp/build/arquivos2", true, true );
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2" ), );
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/f.bat" ), )

    io::deleteFiles( "temp/build", io::by_name_file_filter( "*" ), true );

    io::copyDir( "temp/arquivos", "temp/build", true, false );
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_FALSE( io::fileExists( "temp/build/arquivos/pasta" ), )

    io::copyDir( "temp/arquivos", "temp/build", true, true );
    io::copyDir( "temp/arquivos2", "temp/build", true, true );
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2" ), )

    ASSERT_THROWS( io_error, {
        io::copyDir( "temp/arquivos", "temp/build", false, true );
    }, )
}

TEST_CASE( copyFilesTest, IOTests ) {
    io::copyFiles( "temp/arquivos2", "temp/build", io::by_name_file_filter("*"), true, true );
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/f.bat" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/f.bat" ), )

    ASSERT_THROWS( io_error, {
        io::copyFiles( "temp/arquivos3", "temp/build", io::by_name_file_filter("*"), true, true );
    }, );

    ASSERT_THROWS( io_error, {
        io::copyFiles( "temp/arquivos2", "temp/build2", io::by_name_file_filter("*"), true, true );
    }, );

    io::copyFiles( "temp/arquivos2", "temp/build", "temp", io::by_name_file_filter("*"), true, true );
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/arquivos2/f.bat" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/d.txt" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/e.sh" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos2/f.bat" ), )

    io::copyFiles( "temp/arquivos", "temp/build", "temp", io::by_name_file_filter( "*" ), true, true );
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_TRUE( io::fileExists( "temp/build/arquivos/pasta" ), )
}

TEST_CASE( recursiveDeleteDirTest, IOTests ) {
    int count = io::recursiveDeleteDir( "temp/arquivos" );
    ASSERT_FALSE( io::fileExists( "temp/arquivos" ), )
    ASSERT_EQUALS( count, 8, )
}

TEST_CASE( deleteFileOrDirTest, IOTests ) {
    int count = io::deleteFileOrDir( "temp/b.sh", true );
    ASSERT_FALSE( io::fileExists( "temp/b.sh" ), )
    ASSERT_TRUE( count, 1 );

    ASSERT_THROWS( io_error, {
        count = io::deleteFileOrDir( "temp/arquivos", false );
    }, )

    count = io::deleteFileOrDir( "temp/arquivos", true );
    ASSERT_FALSE( io::fileExists( "temp/arquivos/pasta" ), )
    ASSERT_EQUALS( count, 8, )
}

TEST_CASE( deleteFilesTest, IOTests ) {
    int count;
    
    ASSERT_THROWS( io_error, {
        count = io::deleteFiles( "temp/xxx", io::by_name_file_filter( "*" ), true );
    }, )

    ASSERT_THROWS( io_error, {
        count = io::deleteFiles( "temp/a.txt", io::by_name_file_filter( "*" ), true );
    }, )

    count = io::deleteFiles( "temp/arquivos", io::by_name_file_filter( "*" ), true );
    ASSERT_FALSE( io::fileExists( "temp/arquivos/d.txt" ), )
    ASSERT_FALSE( io::fileExists( "temp/arquivos/e.sh" ), )
    ASSERT_FALSE( io::fileExists( "temp/arquivos/f.bat" ), )
    ASSERT_FALSE( io::fileExists( "temp/arquivos/pasta" ), )
    ASSERT_EQUALS( count, 7, );

    ASSERT_TRUE( io::fileExists( "temp/arquivos1" ), )

    ASSERT_THROWS( io_error, {    
        count = io::deleteFiles( "temp/arquivos1", io::by_name_file_filter( "*" ), false );        
    }, )
}

TEST_CASE( countFilesAndDirsTest, IOTests ) {
    int count = io::countFilesAndDirs( "temp" );
    ASSERT_EQUALS( count, 24, )
}