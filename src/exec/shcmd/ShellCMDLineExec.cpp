
#include "ShellCMDLineExec.h"
#include "../ExecManager.h"
#include "../stexcept.h"
#include "../../io/io.h"
#include "../../shell/shell.h"
#include "../../output/output.h"
#include "../../msg/messagebuilder.h"
#include "../../util/hashutil.h"

#include "../../error_messages.h"
#include "../../info_messages.h"
#include "../../consts.h"

void ShellCMDLineExec::exec( ShellCMDLine* shellCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;

    string cmdstr = shellCMD->getCMDStr();
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( shellCMD );
    bool isShowCMDOutput = manager->getMainCMDArgManager()->isShowCMDOutput( shellCMD );

    Output& out = manager->out;
    
    Shell* shell = new Shell( out );
    shell->setVerbose( isVerbose );
    shell->setShowOutput( isShowCMDOutput );

    int result;
    if ( cmdstr.find( '\n' ) == string::npos ) {
        #ifdef _WIN32
            cmdstr = consts::WINDOWS_CMD_EXE + " " + cmdstr;               
        #endif        

        shell->pushCommand( cmdstr );
        result = shell->execute();
    } else {
        #ifdef _WIN32
            shell->setVerbose( false );

            string shellFileContent = "@echo off\n" + cmdstr;

            int hash = hashutil::currentHash();

            io::createDirs( "temp" );
            
            stringstream ss;
            ss << "temp\\" << hash << ".bat";
            string tempBatFile = ss.str();

            io::writeInTextFile( tempBatFile, shellFileContent );

            cmdstr = ".\\" + tempBatFile;

            shell->pushCommand( cmdstr );
            result = shell->execute();

            io::deleteFileOrDir( tempBatFile, true );
        #else
            shell->pushCommand( cmdstr );
            result = shell->execute();
        #endif
    }

    if ( result != 0 ) {
        messagebuilder b( errors::SHELL_CMD_NOT_EXECUTED );
        b << std::to_string( result );
        throw st_error( shellCMD, b.str() );
    }

    delete shell;
}
