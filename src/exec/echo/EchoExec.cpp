
#include "EchoExec.h"
#include "../ExecManager.h"
#include "../../output/Output.h"
#include "../../util/strutil.h"

#include <iostream>

void EchoExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    Output& inf = manager->inf;
    
    string cmdstr = cmd->getCMDStr();
    string text = strutil::replace( cmdstr, cmd->getName(), "" );
    text = strutil::removeStartWhiteSpaces( text );

    inf << text << "\n";
}
