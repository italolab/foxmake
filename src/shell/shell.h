#ifndef SHELL_H
#define SHELL_H

#include "../output/output.h"

#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;

namespace shell {
    string getWorkingDir();
    bool setWorkingDir( string wdir );
}

class Shell {

    private:
        vector<string> commands;
        bool verboseFlag;
        bool showOutputFlag;

        Output* out;
        Output* inf;

    public:
        Shell( Output& outs );
        
        void pushCommand( string command );
        int execute();

        bool isVerbose();
        bool isShowOutput();
        void setVerbose( bool flag );
        void setShowOutput( bool flag );

};

#endif
