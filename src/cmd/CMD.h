#ifndef CMD_H
#define CMD_H

#include <string>
#include <vector>

using namespace std;

typedef struct TCMDProperty {
    string name;
    string value;
} CMDProperty;

class CMD {

    private:
        string cmdstr;
        string name;
        vector<string> args;
        vector<CMDProperty> properties;

        void addArg( string command );
        void addProperty( string name, string value );

    public:
        void interpreta( string cmdstr );
        void interpreta( int argc, char* argv[] );

        vector<CMDProperty> getProperties();
        CMDProperty getPropertyByIndex( int i );
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

};

#endif
