
#include "EchoExec.h"
#include "../../util/strutil.h"

#include <iostream>
using std::cout;
using std::endl;

void EchoExec::exec( CMD* cmd, void* mgr ) {
    string cmdstr = cmd->getCMDStr();
    string text = strutil::replace( cmdstr, cmd->getName(), "" );
    text = strutil::removeStartWhiteSpaces( text );

    cout << text << endl;
}
