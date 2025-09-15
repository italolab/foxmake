
#include "CDExec.h"
#include "../../stexcept.h"
#include "../../ExecManager.h"
#include "../../../darv/Var.h"
#include "../../../shell/shell.h"
#include "../../../io/io.h"
#include "../../../output/output.h"
#include "../../../msg/messagebuilder.h"

#include "../../../consts.h"
#include "../../../error_messages.h"
#include "../../../info_messages.h"

#include <sstream>

using std::stringstream;
using std::endl;

void CDExec::exec( ExecCMD* execCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    MainScript* script = manager->getMainScript();
    CMD* cmd = execCMD->getCMD();

    Output& out = manager->out;
    bool isVerbose = manager->getMainCMDArgManager()->isVerbose( cmd );
    
    int alen = execCMD->countNoOpArgs();
    if ( alen != 1 ) {
        messagebuilder b( errors::INVALID_NUMBER_OF_ARGS );
        b << "1" << std::to_string( alen );
        throw st_error( cmd, b.str() );
    }

    string newDir = execCMD->getNoOpArgByIndex( 0 );

    if ( !io::fileExists( newDir ) )
        throw st_error( cmd, errors::DIRECTORY_NOT_FOUND );

    if ( !io::isDir( newDir ) )
        throw st_error( cmd, errors::INFORMED_PATH_IS_NOT_A_DIRECTORY );

    bool ok = shell::setWorkingDir( newDir );
    if ( !ok )
        throw st_error( cmd, errors::CURRENT_DIRECTORY_NOT_CHANGED );

    Var* var = script->getLocalVar( "working_dir" );
    if ( var == nullptr )
        throw st_error( cmd, errors::WORKDIR_VAR_NOT_FOUND );

    var->setValue( shell::getWorkingDir() );

    if ( isVerbose ) {
        messagebuilder b( infos::NEW_CURRENT_DIRECTORY );
        b << var->getValue();
        out << b.str() << endl;
    }
}
