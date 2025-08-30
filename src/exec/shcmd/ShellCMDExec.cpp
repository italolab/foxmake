
#include "ShellCMDExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../shell/shell.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

void ShellCMDExec::exec( ShellCMD* shellCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    string cmdstr = shellCMD->getCMDStr();
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( shellCMD );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( shellCMD );

    Output& out = manager->out;
    
    Shell* shell = new Shell( out );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );

    int result;

    #ifdef _WIN32
        if ( cmdstr.find( '\n' ) == string::npos ) {
            shell->pushCommand( consts::WINDOWS_CMD_EXE + " " + cmdstr );
            result = shell->executa();
        } else {
            shell->setVerbose( false );

            string cmdstr2 = "@echo off\n" + cmdstr;

            io::writeInTextFile( consts::TEMP_BAT_FILE, cmdstr2 );
            shell->pushCommand( ".\\" + consts::TEMP_BAT_FILE );
            result = shell->executa();
            io::deleteFileOrDirectory( consts::TEMP_BAT_FILE );
        }
    #else
        shell->pushCommand( cmdstr );
        result = shell->execute();
    #endif

    if ( result != 0 ) {
        messagebuilder b( errors::SHELL_CMD_NOT_EXECUTED );
        b << std::to_string( result );
        throw st_error( shellCMD, b.str() );
    }

    delete shell;
}
