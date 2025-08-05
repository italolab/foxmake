#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "../shell/CMD.h"

#include <vector>
#include <string>

using namespace std;

typedef struct TProperty {
    string name;
    string value;
} Property;

class Config {

    private:
        vector<Property> properties;
        vector<CMD*> cmds;

    public:
        void load( string file, vector<string> validStrCMDs );

        string getPropertyValue( string name );
        CMD* getCMD( string name );

        int getPropertiesLength();
        Property getPropertyByIndex( int i );
        vector<Property> getProperties();

        int getCMDLength();
        CMD* getCMDByIndex( int i );
        vector<CMD*> getCMDs();
};

#endif
