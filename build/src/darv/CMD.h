#ifndef CMD_H
#define CMD_H

#include "No.h"
#include "Property.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class CMD : public No {

    private:
        string name;
        string cmdstr;
        int lineNumber;
        vector<string> args;
        map<string, Property*> propertiesMap;

    public:
        CMD( Block* parent );

        void addProperty( string name, string value );
        vector<string> propertyNames();
        string getPropertyValue( string name );
        int getPropertiesLength();

        void addArg( string command );
        vector<string> getArgs();
        string getArg( int i );
        bool existsArg( string command );
        int getArgsLength();

        string getOpArg( int i );
        string getNotOpArg( int i );

        string getName();
        string getCMDStr();
        int getLineNumber();

        void setName( string name );
        void setCMDStr( string cmdstr );
        void setLineNumber( int lineNumber );

};

#endif
