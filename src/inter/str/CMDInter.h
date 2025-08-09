#ifndef CMD_INTER_H
#define CMD_INTER_H

#include "StringInter.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class CMDInter : public StringInter {

    private:
        string name;
        string cmdstr;
        int lineNumber;
        vector<string> args;
        map<string, string> propertiesMap;

        void addArg( string command );
        void addProperty( string name, string value );

    public:
        CMDInter();

        InterResult* interpreta( string cmdstr, int lineNumber );
        InterResult* interpreta( int argc, char* argv[], int lineNumber );

        vector<string> propertyNames();
        string getPropertyValue( string name );
        int getPropertiesLength();

        vector<string> getArgs();
        string getArg( int i );
        bool existsArg( string command );
        int getArgsLength();

        string getOpArg( int i );
        string getNotOpArg( int i );

        string getName();
        string getCMDStr();
        int getLineNumber();

};

#endif
