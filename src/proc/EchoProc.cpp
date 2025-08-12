
#include "EchoProc.h"
#include "../util/strutil.h"

void EchoProc::processa( CMD* cmd, ProcManager* manager ) {
    string cmdstr = cmd->getCMDStr();
    string text = strutil::replace( cmdstr, cmd->getName(), "" );
    text = strutil::removeStartWhiteSpaces( text );

    cout << text << endl;
}
