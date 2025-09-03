#ifndef CMD_H
#define CMD_H

#include "GenericCMD.h"
#include "Prop.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class CMD : public GenericCMD {

    private:
        string name;
        string cmdstr;
        vector<string> argsVect;
        map<string, Prop*> propertiesMap;

    public:
        CMD( Statement* parent, int numberOfLinesReaded, string line );
        virtual ~CMD();

        void addProperty( Prop* prop );
        vector<string> propertyNames();
        string getPropertyValue( string name );
        int getPropertiesLength();

        void addArg( string command );
        vector<string>& args();
        string getArgByIndex( int i );
        bool existsArg( string command );
        int countOpArgs();
        int countNoOpArgs();
        int getArgsLength();

        string getOpArgByIndex( int i );
        string getNoOpArgByIndex( int i );

        vector<string> getOpArgValues( string op );

        string getName();
        string getCMDStr();

        void setName( string name );
        void setCMDStr( string cmdstr );

        Statement* getTask();

};

#endif
