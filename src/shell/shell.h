#ifndef SHELL_H
#define SHELL_H

#include "../output/output.h"

#include <string>
#include <sstream>
#include <vector>

#include <mutex>
#include <condition_variable>

using std::string;
using std::vector;
using std::stringstream;

namespace shell {
    string getWorkingDir();
    bool setWorkingDir( string wdir );
     
    long getNumberOfProcessorCores();
}

class Shell {

    private:
        vector<string> commands;
        bool verboseFlag;
        bool showOutputFlag;

        Output* out;

    public:
        Shell( Output& outs );
        
        void pushCommand( string command );
        int execute();

        bool isVerbose();
        bool isShowOutput();

        vector<string>& getCommands();
        Output* getOutput();

        void setVerbose( bool flag );
        void setShowOutput( bool flag );

};

#endif
