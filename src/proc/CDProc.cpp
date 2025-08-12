
#include "CDProc.h"
#include "../darv/Var.h"
#include "../shell/shell.h"
#include "../io/io.h"

#include <sstream>

using std::stringstream;

void CDProc::processa( CMD* cmd, ProcManager* manager ) {
    int alen = cmd->getArgsLength();
    if ( alen != 1 ) {
        stringstream ss;
        ss << "Numero de argumentos esperado igual a 1, encontrado " << alen;
        throw proc_error( cmd, ss.str() );
    }

    string newDir = cmd->getArg( 0 );

    if ( !io::fileExists( newDir ) )
        throw proc_error( cmd, "Diretorio nao encontrado." );

    if ( !io::isDirectory( newDir ) )
        throw proc_error( cmd, "O caminho informado nao e um diretorio." );

    bool ok = shell::setWorkingDir( newDir );
    if ( !ok )
        throw proc_error( cmd, "Nao foi possivel alterar o diretorio corrente." );

    Var* var = manager->getMainScript()->getLocalVar( "working_dir" );
    if ( var == nullptr )
        throw runtime_error( "Nao foi encontrada a variavel de diretorio de trabalho." );

    var->setValue( shell::getWorkingDir() );
    cout << "Novo diretorio corrente: " << var->getValue() << endl;
}
