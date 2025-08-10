#ifndef MAIN_SCRIPT_H
#define MAIN_SCRIPT_H

#include "Block.h"
#include "CMD.h"
#include "WithPropNo.h"

#include <string>

using std::string;
using std::vector;

class MainScript : public Block, public WithPropNo {

    private:
        map<string, Prop*> propertiesMap;
        vector<CMD*> cmdsVect;

    public:
        MainScript();

        void addProperty( Prop* prop );
        string getPropertyValue( string name );
        bool existsProperty( string name );
        int getPropertiesLength();
        vector<string> propertyNames();

        void addCMD( CMD* cmd );
        CMD* getCMD( string name );
        int getCMDsLength();
        CMD* getCMDByIndex( int i );
        vector<CMD*> cmds();
};

#endif
