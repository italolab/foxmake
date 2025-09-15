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

        CMD* newCopy();

        void addProperty( Prop* prop );
        vector<string> propertyNames();
        string getPropertyValue( string name );
        int getPropertiesLength();
        map<string, Prop*>& getPropsMap();

        void addArg( string command );
        vector<string>& getArgs();
        string getArgByIndex( int i );
        bool existsArg( string command );
        int getArgsLength();

        string getName();
        string getCMDStr();

        void setName( string name );
        void setCMDStr( string cmdstr );

        Statement* getTask();

};

#endif
