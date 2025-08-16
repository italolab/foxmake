
#include "ShellCMDProc.h"
#include "../stexcept.h"
#include "../../shell/shell.h"

#include <iostream>

using std::cout;
using std::endl;

void ShellCMDProc::proc( ShellCMD* shellCMD, void* mgr ) {
    string cmdstr = shellCMD->getCMDStr();

    Shell* shell = new Shell( true );
    shell->pushCommand( "cmd.exe /c "+cmdstr );

    int result = shell->executa();
    if ( result != 0 ) {
        stringstream ss;
        ss << "Nao foi possivel executar o comando." << endl;
        ss << "Verifique se ele existe e sua sintaxe!" << endl;
        ss << "O comando retornou o codigo: " << result;
        throw st_error( shellCMD, ss.str() );
    }

    delete shell;

    cout << "Executado: " << cmdstr << endl;

}
