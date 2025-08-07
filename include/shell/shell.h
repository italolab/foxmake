#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Shell {

    private:
        vector<string> commands;
        bool isPrintOutput;

    public:
        stringstream out;
        stringstream err;

        Shell( bool isPrintOutput = false );

        void pushCommand( string command );
        bool executa();

};

#endif
