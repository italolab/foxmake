
#include "EchoExec.h"
#include "../../ExecManager.h"
#include "../../../output/output.h"
#include "../../../util/strutil.h"

#include <iostream>

using std::endl;

void EchoExec::exec( CMD* cmd, void* mgr ) {
    ExecManager* manager = (ExecManager*)mgr;
    Output& out = manager->out;

    vector<string>& args = cmd->getArgs();
    int len = args.size();
    for( int i = 0; i < len; i++ ) {
        out << args[ i ];
        if ( i < len-1 )
            out << " ";
    }
    out << "\n";
}
