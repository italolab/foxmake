
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
}

AFTER_EACH( IOTests ) {
    io::deleteFiles( "temp", io::by_name_file_filter( "*" ) ); 
}

TEST_CASE( copyFileTest, IOTests ) {
    io::copyFile( "temp/b.sh", "temp/build/b.sh", true );
    io::copyFile( "temp/b.sh", "temp/build/c.sh", true );

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
}

TEST_CASE( copyDirTest, IOTests ) {
    ASSERT_TRUE( io::fileExists( "temp/build" ), )

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

    io::deleteFiles( "temp/build", io::by_name_file_filter( "*" ) );

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

TEST_CASE( copyDirToDirTest, IOTests ) {
    ASSERT_FALSE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_FALSE( io::isEmptyDir( "temp/arquivos" ), )

    ASSERT_THROWS( io_error,
        io::copyDirToDir( "temp/arquivos", "temp/build/arquivos", true, true );
    , )

    ASSERT_NOT_THROWS( io_error, 
        io::copyDirToDir( "temp/arquivos", "temp/build", true, true );
    , )

    ASSERT_TRUE( io::fileExists( "temp/build/arquivos" ), )
    ASSERT_FALSE( io::isEmptyDir( "temp/build/arquivos" ), )
}