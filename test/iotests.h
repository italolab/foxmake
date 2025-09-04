
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
    
}