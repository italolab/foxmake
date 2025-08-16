#ifndef SHELL_H
#define SHELL_H

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
        bool isPrintOutput;

    public:
        stringstream out;
        stringstream err;

        Shell( bool isPrintOutput = false );

        void pushCommand( string command );
        int executa();

};

#endif
