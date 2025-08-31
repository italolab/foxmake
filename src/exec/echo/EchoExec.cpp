
#include "EchoExec.h"
#include "../ExecManager.h"
#include "../../output/output.h"
#include "../../util/strutil.h"

#include <iostream>

using std::endl;

void EchoExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    Output& out = manager->out;
    
    string cmdstr = cmd->getCMDStr();
    string text = strutil::replace( cmdstr, cmd->getName(), "" );
    text = strutil::removeStartWhiteSpaces( text );

    out << output::green( text ) << endl;
}
