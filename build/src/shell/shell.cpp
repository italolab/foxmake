#include <windows.h>
#include <iostream>

#include "shell.h"

Shell::Shell( bool isPrintOutput ) {
    this->isPrintOutput = isPrintOutput;
}

void Shell::pushCommand( string command ) {
    commands.push_back( command );
}

bool Shell::executa() {
    STARTUPINFO si = { sizeof( si ) };

    vector<PROCESS_INFORMATION> vectPIs;
    bool isError = false;

    for( string command : commands ) {
        PROCESS_INFORMATION pi;

        WINBOOL result = CreateProcess( NULL, const_cast<char*>( command.c_str() ), NULL, NULL, false, 0, NULL, NULL, &si, &pi );
        if ( result ) {
            vectPIs.push_back( pi );

            if ( isPrintOutput )
                cout << command << endl;
        } else {
            string msg = "cmd nao executado: " + command;

            if ( isPrintOutput )
                cerr << msg << endl;

            err << msg << endl;
            isError = true;
            break;
        }
    }

    for( PROCESS_INFORMATION pi : vectPIs ) {
        WaitForSingleObject( pi.hProcess, INFINITE );

        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }

    return !isError;
}
