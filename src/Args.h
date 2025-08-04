#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <vector>

using namespace std;

typedef struct TArg {
    string name;
    string value;
} Arg;

class Args {

    private:
        vector<string> commands;
        vector<Arg> args;
        bool errorFound;
        string error;

    public:
        Args();

        void addCommand( string command );
        void addArg( string name, string value );
        void setError( string err );
        vector<string> getCommands();
        vector<Arg> getArgs();
        string getCommand( int i );
        bool existsCommand( string command );
        Arg getArg( int i );
        int getCommandsLength();
        int getArgsLength();
        bool isErrorFound();
        string getError();

};

#endif
