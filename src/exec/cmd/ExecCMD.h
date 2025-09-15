#ifndef CMD2_H
#define CMD2_H

#include "../../darv/CMD.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class ExecCMD {

    private:
        string name;
        string cmdstr;

        vector<string> argsVect;
        map<string, Prop*> propsMap;

        CMD* cmd;

    public:
        ExecCMD( CMD* cmd );

        string getPropertyValue( string name );
        Prop* getProperty( string name );

        vector<string>& getArgs();
        string getArgByIndex( int i );
        bool existsArg( string command );
        int getArgsLength();

        int countOpArgs();
        int countNoOpArgs();

        string getOpArgByIndex( int i );
        string getNoOpArgByIndex( int i );

        vector<string> getOpArgValues( string op );

        string getLine();
        string getName();
        string getCMDStr();
        CMD* getCMD();

        void setCMDStr( string cmdstr );

};

#endif