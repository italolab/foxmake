
#include "EchoExec.h"
#include "../../ExecManager.h"
#include "../../../output/output.h"
#include "../../../util/strutil.h"

#include <iostream>

using std::endl;

void EchoExec::exec( ExecCMD* execCMD, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    Output& out = manager->out;

    string cmdstr = execCMD->getCMDStr();
    string cmdName = execCMD->getName();

    string echoContent = strutil::replace( cmdstr, cmdName, "" );
    echoContent = strutil::removeStartWhiteSpaces( echoContent );

    out << echoContent << "\n";
}
