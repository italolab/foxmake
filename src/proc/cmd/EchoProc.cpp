
#include "EchoProc.h"
#include "../../util/strutil.h"

#include <iostream>
using std::cout;
using std::endl;

void EchoProc::proc( CMD* cmd, void* mgr ) {
    string cmdstr = cmd->getCMDStr();
    string text = strutil::replace( cmdstr, cmd->getName(), "" );
    text = strutil::removeStartWhiteSpaces( text );

    cout << text << endl;
}
